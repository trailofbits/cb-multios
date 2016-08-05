/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "certificate.h"
#include "util.h"
#include "malloc.h"
#include "strncmp.h"
#include "cbstdio.h"
#include "memcpy.h"
#include "strtok.h"
#include "comms.h"
#include <libcgc.h>

/**
* Is the command a valud Certificate command
* 
* @param command the command string
*
* @return 1 if true, 0 if false
*/
int isCertCommand(char* command) {

	if(!strncmp(command, ENROLL_CMD, strlen(ENROLL_CMD)))
		return 1;

	if(!strncmp(command, REENROLL_CMD, strlen(REENROLL_CMD)))
		return 1;

	if(!strncmp(command, CERTS_CMD, strlen(CERTS_CMD)))
		return 1;

	if(!strncmp(command, REVOKE_CERT_CMD, strlen(REVOKE_CERT_CMD)))
		return 1;

	return 0;
}

/**
* Initialzie issuer string
*
* @return None
*/
void initIssuer() {
	if(!(issuer = malloc(64)))
		_terminate(1);
	bzero(issuer, 64);
	memcpy(issuer, ISSUER_STR, strlen(ISSUER_STR));		
}

/**
* Sign the certificate
* 
* @param cert The address of the Certificate to sign
*
* @return None
*/
void signCert(Certificate** cert) {
	Certificate *signedCert;
	size_t size=0;
	unsigned int signature=0;
	int i;

	signedCert = *cert;
	size = strlen(signedCert->issuer);
	for(i=0; i<size; i++)
		signature += signedCert->issuer[i];

	size = strlen(signedCert->subject);
	for(i=0; i<size; i++)
		signature += signedCert->subject[i];

	size = strlen(signedCert->key);
	for(i=0; i<size; i++)
		signature += signedCert->key[i];

	signature += signedCert->expiration;

	size = strlen(private_key);
	for(i=0; i<size; i++)
		signature += private_key[i];	

	if(signedCert->revoked) {
		size = strlen(signedCert->revoked);
		for(i=0; i<size; i++)
			signature += signedCert->revoked[i];
	}

	signedCert->signature = signature;

}

/**
* Calculate how many bytes are needed to store the Certificate as a string
* 
* @param cert The address of the Certificate
*
* @return The number of bytes to store the Certificate as a string
*/
size_t calculateCertSize(Certificate *cert) {
	size_t size;

	size = strlen(CERT_ISSUER_HDR) +1;
	size += strlen(cert->issuer) + 1;
	size += strlen(CERT_SUBJECT_HDR) + 1;
	size += strlen(cert->subject) + 1;
	size += strlen(CERT_KEY_HDR) + 1;
	size += strlen(cert->key) + 1;
	size += strlen(CERT_SIG_HDR) + 1;
	size += MAX_UINT_STR_SIZE + 1; //signature
	size += strlen(CERT_EXP_HDR) + 1;
	size += MAX_UINT_STR_SIZE + 1; //expiration
	size += strlen(CERT_USE_HDR) + 1;
	size += strlen(cert->use) + 1;
	if(cert->revoked) {
		size += strlen(CERT_STATUS_HDR) + 1;
		size += strlen(cert->revoked) + 1;		
	}


	return size;
}

/**
* Send the certificate as a string to the requestor
* 
* @param id The id of the initial requesting message
* @param cert The certificate to send
*
* @return None
*/
void sendCerts(unsigned int id, Certificate *cert) {
	Certificate *cert_ptr;
	int first=1;
	size_t certSize, bytes;
	char* buffer;
	int ret;

	for(cert_ptr=cert;cert_ptr != 0; cert_ptr=cert_ptr->next) {
		if(!first) {
			if((ret = transmit_all(STDOUT, "|", sizeof("|")))) 
				_terminate(1);	
		} else {
			first = 0;
		}

		certSize = calculateCertSize(cert);
		if(!(buffer = malloc(certSize+10)))
			_terminate(1);
		bzero(buffer, certSize+10);
		if(cert->revoked) {
			sprintf(buffer, "!X=!X;!X=!X;!X=!X;!X=!U;!X=!U;!X=!X;!X=!X",
				CERT_ISSUER_HDR, cert->issuer,
				CERT_SUBJECT_HDR, cert->subject,
				CERT_KEY_HDR, cert->key,
				CERT_SIG_HDR, cert->signature,
				CERT_EXP_HDR, cert->expiration,
				CERT_USE_HDR, cert->use,
				CERT_STATUS_HDR, cert->revoked);			
		} else {
			sprintf(buffer, "!X=!X;!X=!X;!X=!X;!X=!U;!X=!U;!X=!X",
				CERT_ISSUER_HDR, cert->issuer,
				CERT_SUBJECT_HDR, cert->subject,
				CERT_KEY_HDR, cert->key,
				CERT_SIG_HDR, cert->signature,
				CERT_EXP_HDR, cert->expiration,
				CERT_USE_HDR, cert->use);			
		}

		certSize = strlen(buffer);
		if((ret = transmit_all(STDOUT, buffer, certSize))) 
			_terminate(1);
		free(buffer);
	}

	if((ret = transmit_all(STDOUT, "?", strlen("?")))) 
		_terminate(1);

}

/**
* Parse the buffer as a Certificate
* 
* @param buffer The buffer that contains the string
*
* @return The address of the new Certificate
*/
Certificate *parseCertificate(char* body) {
	Certificate *cert;

	cert = malloc(sizeof(Certificate));
	if(!cert)
		_terminate(1);

	bzero((char *)cert, sizeof(Certificate));

	initializeAttributes(body);
	getStringAttribute(&cert->issuer, CERT_ISSUER_HDR);
	getStringAttribute(&cert->subject, CERT_SUBJECT_HDR);
	getStringAttribute(&cert->key, CERT_KEY_HDR);
	getIntegerAttribute(&cert->signature, CERT_SIG_HDR);
	getIntegerAttribute(&cert->expiration, CERT_EXP_HDR);
	getStringAttribute(&cert->use, CERT_USE_HDR);
	getStringAttribute(&cert->revoked, CERT_STATUS_HDR);
	getIntegerAttribute(&cert->exp_window, CERT_EXP_WDOW_HDR);

	return cert;
}

/**
* Check to see if Certificate is in the Certiifcate Revocation List
* 
* @param cert The address of the certificate
*
* @return 1 if certificate is in the list, 0 if not
*/
int checkCRLs(Certificate *cert) {
	Certificate *revoked_cert;
	size_t size, size1, size2;

	for(revoked_cert=CRL; revoked_cert != NULL; revoked_cert=revoked_cert->next) {
		size1 = strlen(revoked_cert->subject);
		size2 = strlen(cert->subject);
		size = size1 > size2 ? size1 : size2;
		if(!strncmp(revoked_cert->subject, cert->subject, size)) {
			size1 = strlen(revoked_cert->key);
			size2 = strlen(cert->key);
			size = size1 > size2 ? size1 : size2;		
			if(!strncmp(revoked_cert->key, cert->key, size))
				return 0;
		}
	}

	return 1;
}

/**
* Ensure the Certificate is valid
* 
* @param cert The address of the certificate to check
* @param use The command the requestor wants to use the certificate for
* @param expiration_date The current date
*
* @return 1 if certificate is valid, 0 if it is not
*/
int validateCert(Certificate *cert, char* use, unsigned int* expiration_date) {
	unsigned int tmp_sig;

	if(!cert->issuer || !cert->subject || !cert->key || !cert->signature || !cert->expiration || !cert->use) {
		sendErrorResponse(RESPONSE_ERR_NO_CERT);

		return 0;		
	}

	if(strncmp(cert->issuer, issuer, strlen(ISSUER_STR))) {
		sendErrorResponse(RESPONSE_ERR_NO_CERT);

		return 0;
	}

	if(cert->revoked)
		if(!strncmp(cert->revoked, CERT_STATUS_REVOKED, strlen(CERT_STATUS_REVOKED)))
			return 0;

	tmp_sig = cert->signature;
	signCert(&cert);
	*expiration_date += 1;

	if(tmp_sig == cert->signature && cert->expiration > *expiration_date)
		return checkCRLs(cert);

	if(cert->expiration > *expiration_date) {
		sendErrorResponse(RESPONSE_ERR_NO_CERT);

		return 0;		
	}

	sendErrorResponse(RESPONSE_ERR_EXP_CERT);

	return 0;
}

/**
* Send the current Certificate Revocation List to the requestor
* 
* @param id The id of the initial requesting message
* @param body The body of the requesting message
* @param expiration_date The current date
*
* @return None
*/
void crls(int id, char* body, unsigned int* expiration_date) {
	sendCerts(id, CRL);
}

/**
* Deallocate the memory used for the certificate
* 
* @param cert The address of the certificate
*
* @return None
*/
void freeCert(Certificate* cert) {

	free(cert->subject);
	free(cert->issuer);
	free(cert->key);
	free(cert->use);
	free(cert->next);
	if(cert->revoked)
		free(cert->revoked);
	free(cert);
}

/**
* Revoke the cert contained in the body of the requesting message
* 
* @param id The id of the initial requesting message
* @param body The body of the requesting message
* @param expiration_date The current date
*
* @return None
*/
void revokeCert(int id, char* body, unsigned int* expiration_date) {
	Certificate *cert;
	int ret;
	size_t size;

	if(!(cert = parseCertificate(body)))
		return;

	if(!(ret = validateCert(cert, NULL, expiration_date)))
		return;

	size = strlen(CERT_STATUS_REVOKED);
	if(!(cert->revoked = malloc(size+1)))
		_terminate(1);
	bzero(cert->revoked, size+1);
	memcpy(cert->revoked, CERT_STATUS_REVOKED, size);
	signCert(&cert);
	cert->next = NULL;
	sendCerts(id, cert);
	cert->next = CRL;
	CRL = cert;
}

/**
* Reenroll the cert contained in the body of the requesting message
* 
* @param id The id of the initial requesting message
* @param body The body of the requesting message
* @param expiration_date The current date
*
* @return None
*/
void reenroll(int id, char* body, unsigned int* expiration_date) {
	Certificate *cert;
	int ret;
	unsigned int expire_window=100;

	if(!(cert = parseCertificate(body))) 
		return;
	
	if(!(ret = validateCert(cert, NULL, expiration_date))) 
		return;

	if(cert->exp_window)
		expire_window = cert->exp_window;

	*expiration_date += 1;
	cert->expiration = *expiration_date + expire_window;
	signCert(&cert);
	sendCerts(id, cert);
	freeCert(cert);
}

/**
* Check that the certificate is allowed to be used for the command
* 
* @param command The command the requestor wants to use the certificate for
* @param useList The list of uses contained in the certificate
*
* @return 1 if use is valid, 0 if it is not
*/
int checkCertUse(char* command, char* useList) {
	char* use;
	size_t size, size1, size2;

	if(!useList)
		return 0;

	use = strtok(useList,":");
	do {
		size1 = strlen(command);
		size2 = strlen(use);
		size = size1 > size2 ? size1 : size2;
		if(!strncmp(command, use, size) ||
			!strncmp(REVOKE_CERT_CMD, use, strlen(REVOKE_CERT_CMD)))
			return 1;

		use = strtok(0, ":");
	} while(use);

	return 0;

}

/**
* Enroll the cert contained in the body of the requesting message
* 
* @param id The id of the initial requesting message
* @param body The body of the requesting message
* @param expiration_date The current date
*
* @return None
*/
void enroll(int id, char* body, unsigned int* expiration_date) {
	Certificate *cert;
	size_t size;
	unsigned int expire_window=100;

	if(!issuer) {
		initIssuer();
	}

	cert = parseCertificate(body);

	if(!cert->subject || !cert->key || !cert->use) {
		sendErrorResponse(RESPONSE_ERR_NO_CERT);

		return;		
	}

	if(cert->issuer)
		free(cert->issuer);

	size = strlen(issuer);
	if(!(cert->issuer = malloc(size+1)))
		_terminate(1);
	bzero(cert->issuer, size+1);
	memcpy(cert->issuer, issuer, size);

	if(!cert->subject)
		return;

	if(!cert->key) 
		return;

	if(cert->exp_window)
		expire_window = cert->exp_window;

	*expiration_date += 1;
	cert->expiration = *expiration_date + expire_window;
	cert->next = 0;
	signCert(&cert); 
	sendCerts(id, cert);
	freeCert(cert);

}