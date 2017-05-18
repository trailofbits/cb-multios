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
#include "cgc_certificate.h"
#include "cgc_util.h"
#include "cgc_malloc.h"
#include "cgc_strncmp.h"
#include "cgc_cbstdio.h"
#include "cgc_memcpy.h"
#include "cgc_strtok.h"
#include "cgc_comms.h"
#include "libcgc.h"

/**
* Is the command a valud Certificate command
* 
* @param command the command string
*
* @return 1 if true, 0 if false
*/
int cgc_isCertCommand(char* command) {

	if(!cgc_strncmp(command, ENROLL_CMD, cgc_strlen(ENROLL_CMD)))
		return 1;

	if(!cgc_strncmp(command, REENROLL_CMD, cgc_strlen(REENROLL_CMD)))
		return 1;

	if(!cgc_strncmp(command, CERTS_CMD, cgc_strlen(CERTS_CMD)))
		return 1;

	if(!cgc_strncmp(command, REVOKE_CERT_CMD, cgc_strlen(REVOKE_CERT_CMD)))
		return 1;

	return 0;
}

/**
* Initialzie issuer string
*
* @return None
*/
void cgc_initIssuer() {
	if(!(issuer = cgc_malloc(64)))
		cgc__terminate(1);
	cgc_bzero(issuer, 64);
	cgc_memcpy(issuer, ISSUER_STR, cgc_strlen(ISSUER_STR));		
}

/**
* Sign the certificate
* 
* @param cert The address of the Certificate to sign
*
* @return None
*/
void cgc_signCert(Certificate** cert) {
	Certificate *signedCert;
	cgc_size_t size=0;
	unsigned int signature=0;
	int i;

	signedCert = *cert;
	size = cgc_strlen(signedCert->issuer);
	for(i=0; i<size; i++)
		signature += signedCert->issuer[i];

	size = cgc_strlen(signedCert->subject);
	for(i=0; i<size; i++)
		signature += signedCert->subject[i];

	size = cgc_strlen(signedCert->key);
	for(i=0; i<size; i++)
		signature += signedCert->key[i];

	signature += signedCert->expiration;

	size = cgc_strlen(private_key);
	for(i=0; i<size; i++)
		signature += private_key[i];	

	if(signedCert->revoked) {
		size = cgc_strlen(signedCert->revoked);
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
cgc_size_t cgc_calculateCertSize(Certificate *cert) {
	cgc_size_t size;

	size = cgc_strlen(CERT_ISSUER_HDR) +1;
	size += cgc_strlen(cert->issuer) + 1;
	size += cgc_strlen(CERT_SUBJECT_HDR) + 1;
	size += cgc_strlen(cert->subject) + 1;
	size += cgc_strlen(CERT_KEY_HDR) + 1;
	size += cgc_strlen(cert->key) + 1;
	size += cgc_strlen(CERT_SIG_HDR) + 1;
	size += MAX_UINT_STR_SIZE + 1; //signature
	size += cgc_strlen(CERT_EXP_HDR) + 1;
	size += MAX_UINT_STR_SIZE + 1; //expiration
	size += cgc_strlen(CERT_USE_HDR) + 1;
	size += cgc_strlen(cert->use) + 1;
	if(cert->revoked) {
		size += cgc_strlen(CERT_STATUS_HDR) + 1;
		size += cgc_strlen(cert->revoked) + 1;		
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
void cgc_sendCerts(unsigned int id, Certificate *cert) {
	Certificate *cert_ptr;
	int first=1;
	cgc_size_t certSize, bytes;
	char* buffer;
	int ret;

	for(cert_ptr=cert;cert_ptr != 0; cert_ptr=cert_ptr->next) {
		if(!first) {
			if((ret = cgc_transmit_all(STDOUT, "|", sizeof("|")))) 
				cgc__terminate(1);	
		} else {
			first = 0;
		}

		certSize = cgc_calculateCertSize(cert);
		if(!(buffer = cgc_malloc(certSize+10)))
			cgc__terminate(1);
		cgc_bzero(buffer, certSize+10);
		if(cert->revoked) {
			cgc_sprintf(buffer, "!X=!X;!X=!X;!X=!X;!X=!U;!X=!U;!X=!X;!X=!X",
				CERT_ISSUER_HDR, cert->issuer,
				CERT_SUBJECT_HDR, cert->subject,
				CERT_KEY_HDR, cert->key,
				CERT_SIG_HDR, cert->signature,
				CERT_EXP_HDR, cert->expiration,
				CERT_USE_HDR, cert->use,
				CERT_STATUS_HDR, cert->revoked);			
		} else {
			cgc_sprintf(buffer, "!X=!X;!X=!X;!X=!X;!X=!U;!X=!U;!X=!X",
				CERT_ISSUER_HDR, cert->issuer,
				CERT_SUBJECT_HDR, cert->subject,
				CERT_KEY_HDR, cert->key,
				CERT_SIG_HDR, cert->signature,
				CERT_EXP_HDR, cert->expiration,
				CERT_USE_HDR, cert->use);			
		}

		certSize = cgc_strlen(buffer);
		if((ret = cgc_transmit_all(STDOUT, buffer, certSize))) 
			cgc__terminate(1);
		cgc_free(buffer);
	}

	if((ret = cgc_transmit_all(STDOUT, "?", cgc_strlen("?")))) 
		cgc__terminate(1);

}

/**
* Parse the buffer as a Certificate
* 
* @param buffer The buffer that contains the string
*
* @return The address of the new Certificate
*/
Certificate *cgc_parseCertificate(char* body) {
	Certificate *cert;

	cert = cgc_malloc(sizeof(Certificate));
	if(!cert)
		cgc__terminate(1);

	cgc_bzero((char *)cert, sizeof(Certificate));

	cgc_initializeAttributes(body);
	cgc_getStringAttribute(&cert->issuer, CERT_ISSUER_HDR);
	cgc_getStringAttribute(&cert->subject, CERT_SUBJECT_HDR);
	cgc_getStringAttribute(&cert->key, CERT_KEY_HDR);
	cgc_getIntegerAttribute(&cert->signature, CERT_SIG_HDR);
	cgc_getIntegerAttribute(&cert->expiration, CERT_EXP_HDR);
	cgc_getStringAttribute(&cert->use, CERT_USE_HDR);
	cgc_getStringAttribute(&cert->revoked, CERT_STATUS_HDR);
	cgc_getIntegerAttribute(&cert->exp_window, CERT_EXP_WDOW_HDR);

	return cert;
}

/**
* Check to see if Certificate is in the Certiifcate Revocation List
* 
* @param cert The address of the certificate
*
* @return 1 if certificate is in the list, 0 if not
*/
int cgc_checkCRLs(Certificate *cert) {
	Certificate *revoked_cert;
	cgc_size_t size, size1, size2;

	for(revoked_cert=CRL; revoked_cert != NULL; revoked_cert=revoked_cert->next) {
		size1 = cgc_strlen(revoked_cert->subject);
		size2 = cgc_strlen(cert->subject);
		size = size1 > size2 ? size1 : size2;
		if(!cgc_strncmp(revoked_cert->subject, cert->subject, size)) {
			size1 = cgc_strlen(revoked_cert->key);
			size2 = cgc_strlen(cert->key);
			size = size1 > size2 ? size1 : size2;		
			if(!cgc_strncmp(revoked_cert->key, cert->key, size))
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
int cgc_validateCert(Certificate *cert, char* use, unsigned int* expiration_date) {
	unsigned int tmp_sig;

	if(!cert->issuer || !cert->subject || !cert->key || !cert->signature || !cert->expiration || !cert->use) {
		cgc_sendErrorResponse(RESPONSE_ERR_NO_CERT);

		return 0;		
	}

	if(cgc_strncmp(cert->issuer, issuer, cgc_strlen(ISSUER_STR))) {
		cgc_sendErrorResponse(RESPONSE_ERR_NO_CERT);

		return 0;
	}

	if(cert->revoked)
		if(!cgc_strncmp(cert->revoked, CERT_STATUS_REVOKED, cgc_strlen(CERT_STATUS_REVOKED)))
			return 0;

	tmp_sig = cert->signature;
	cgc_signCert(&cert);
	*expiration_date += 1;

	if(tmp_sig == cert->signature && cert->expiration > *expiration_date)
		return cgc_checkCRLs(cert);

	if(cert->expiration > *expiration_date) {
		cgc_sendErrorResponse(RESPONSE_ERR_NO_CERT);

		return 0;		
	}

	cgc_sendErrorResponse(RESPONSE_ERR_EXP_CERT);

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
void cgc_crls(int id, char* body, unsigned int* expiration_date) {
	cgc_sendCerts(id, CRL);
}

/**
* Deallocate the memory used for the certificate
* 
* @param cert The address of the certificate
*
* @return None
*/
void cgc_freeCert(Certificate* cert) {

	cgc_free(cert->subject);
	cgc_free(cert->issuer);
	cgc_free(cert->key);
	cgc_free(cert->use);
	cgc_free(cert->next);
	if(cert->revoked)
		cgc_free(cert->revoked);
	cgc_free(cert);
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
void cgc_revokeCert(int id, char* body, unsigned int* expiration_date) {
	Certificate *cert;
	int ret;
	cgc_size_t size;

	if(!(cert = cgc_parseCertificate(body)))
		return;

	if(!(ret = cgc_validateCert(cert, NULL, expiration_date)))
		return;

	size = cgc_strlen(CERT_STATUS_REVOKED);
	if(!(cert->revoked = cgc_malloc(size+1)))
		cgc__terminate(1);
	cgc_bzero(cert->revoked, size+1);
	cgc_memcpy(cert->revoked, CERT_STATUS_REVOKED, size);
	cgc_signCert(&cert);
	cert->next = NULL;
	cgc_sendCerts(id, cert);
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
void cgc_reenroll(int id, char* body, unsigned int* expiration_date) {
	Certificate *cert;
	int ret;
	unsigned int expire_window=100;

	if(!(cert = cgc_parseCertificate(body))) 
		return;
	
	if(!(ret = cgc_validateCert(cert, NULL, expiration_date))) 
		return;

	if(cert->exp_window)
		expire_window = cert->exp_window;

	*expiration_date += 1;
	cert->expiration = *expiration_date + expire_window;
	cgc_signCert(&cert);
	cgc_sendCerts(id, cert);
	cgc_freeCert(cert);
}

/**
* Check that the certificate is allowed to be used for the command
* 
* @param command The command the requestor wants to use the certificate for
* @param useList The list of uses contained in the certificate
*
* @return 1 if use is valid, 0 if it is not
*/
int cgc_checkCertUse(char* command, char* useList) {
	char* use;
	cgc_size_t size, size1, size2;

	if(!useList)
		return 0;

	use = cgc_strtok(useList,":");
	do {
		size1 = cgc_strlen(command);
		size2 = cgc_strlen(use);
		size = size1 > size2 ? size1 : size2;
		if(!cgc_strncmp(command, use, size) ||
			!cgc_strncmp(REVOKE_CERT_CMD, use, cgc_strlen(REVOKE_CERT_CMD)))
			return 1;

		use = cgc_strtok(0, ":");
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
void cgc_enroll(int id, char* body, unsigned int* expiration_date) {
	Certificate *cert;
	cgc_size_t size;
	unsigned int expire_window=100;

	if(!issuer) {
		cgc_initIssuer();
	}

	cert = cgc_parseCertificate(body);

	if(!cert->subject || !cert->key || !cert->use) {
		cgc_sendErrorResponse(RESPONSE_ERR_NO_CERT);

		return;		
	}

	if(cert->issuer)
		cgc_free(cert->issuer);

	size = cgc_strlen(issuer);
	if(!(cert->issuer = cgc_malloc(size+1)))
		cgc__terminate(1);
	cgc_bzero(cert->issuer, size+1);
	cgc_memcpy(cert->issuer, issuer, size);

	if(!cert->subject)
		return;

	if(!cert->key) 
		return;

	if(cert->exp_window)
		expire_window = cert->exp_window;

	*expiration_date += 1;
	cert->expiration = *expiration_date + expire_window;
	cert->next = 0;
	cgc_signCert(&cert); 
	cgc_sendCerts(id, cert);
	cgc_freeCert(cert);

}