/*
 The MULTIPASS PROTOCOL is used to process the operations of a multi-use
 RFID payment card (i.e. Multi-pass) and record them in a transaction log.
 It can also issue new multi-pass cards.


** Operations **
 There are 6 types of multi-pass operations:

	typedef enum {
		PURCHASE = 0,	// 0
		RECHARGE,		// 1
		BALANCE,		// 2
		HISTORY,		// 3
		ISSUE,			// 4
		REFUND			// 5
	} OP_CODE;

 - PURCHASE: multi-pass is used at a vendor to make a purchase.
 - RECHARGE: multi-pass is used at a vendor to add money to the card balance.
 - BALANCE: multi-pass is used to query its balance.
 - HISTORY: multi-pass is used to query its last N transactions.
 - ISSUE: a new multi-pass card is issued with a given starting balance.
 - REFUND: multi-pass is used to cancel a purchase and refund the payment 
 	amount to the card's balance. The original purchase transaction is removed from
 	the server's transaction log.

 Each operation type involves a sequence of packets. 
	* Types of Packets *
	typedef enum {
		INIT = 0,	// 0
		AUTH,		// 1
		OPS,		// 2
		FIN 		// 3
	} PKT_TYPE;

 * Packet Sequence Overview *
 For all operations, except ISSUE:
 1. The first packet is of type AUTH. The server uses this packet to verify that
 the card_id / auth_code are on record and if so, to start a new transaction log entry and mark
 the transaction as 'AUTH'.
 2. The second packet is of type OPS. If a previous AUTH was completed for the 
 given transaction ID and card (ID/auth_code),
 the server uses this packet to perform the given operation and mark the transaction as operation 'OPS'.
 3. The final packet is of type FIN. If a previous OPS was completed for the 
 given transaction ID and card (ID/auth_code),
 the server uses this packet to mark the transaction as complete 'FIN'.

 For the ISSUE operation, it cannot AUTH since AUTH requires a valid card.
 And the purpose of ISSUE is to issue a new multi-pass card.
 1. The first packet is of type INIT. The server uses this packet to create a new card using
 the next card id, the next auth_code, and the client-provided inital balance. It also
 starts a new transaction log marked as 'INIT'.
 2. The final packet is of type FIN. If a previous INIT was completed for the 
 given transaction ID and card (ID/auth_code), 
 the server uses this packet to mark the transaction as complete 'FIN'.

** Communications - client<->server **

	* Common Packet Header *
		uint32_t card_id;			// 4 bytes
		uint32_t auth_code;			// 4 bytes
		PKT_TYPE pkt_type : 8;		// 1 byte
		OP_CODE op_code : 8;		// 1 byte
		STATUS status : 8;			// 1 byte
		uint32_t transaction_id;	// 4 bytes

	* Error Data *
		uint32_t 		length;
		char[length] 	msg;

	* Issue Data *
		uint32_t amount;

	* Balance Data *
		uint32_t balance;

	* History Data *
		uint32_t count;

	* Purchase Data *
		uint32_t purchase_id;
		uint32_t cost;
		// Vendor Data goes here

	* Recharge Data *
		uint32_t amount;
		// Vendor Data goes here

	* Refund Data *
		uint32_t purchase_id;
		uint32_t transaction_id;

	* Vendor Data *
		uint32_t 					vendor_id;			
		VENDOR_TYPE 				vendor_type : 8;
		uint8_t 					vendor_location_sz;
		char[vendor_location_sz] 	vendor_location;

 * ALL operations *
 server -> client (PKT_TYPE = INIT or AUTH or OPS or FIN)
 - IFF Common Packet Header status is non-zero, server sends Error Data
 -- msg is the error message associated with status; does not contain a trailing '\0'
 -- length is the number of char's in msg
 - See Errors section below.

 * PURCHASE operation *
 OP_CODE = PURCHASE

 client -> server (PKT_TYPE = AUTH)
 - client sends Common Packet Header
 -- card_id and auth_code must be from a previously issued card
 -- status and transaction_id are unused (recommend to set to 0).
 server -> client (PKT_TYPE = AUTH)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the newly initiated transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 client -> server (PKT_TYPE = OPS)
 - client sends Common Packet Header followed by Purchase Data and associated Vendor Data
 -- card_id and auth_code must be from the card used during AUTH.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 -- amount should be <= max uint32 - balance on card
 -- purchase_id, vendor_id, vendor_location can be any random values
 -- vendor_type can be any value from VENDOR_TYPE enum
 server -> client (PKT_TYPE = OPS)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 client -> server (PKT_TYPE = FIN)
 - client sends Common Packet Header
 -- card_id and auth_code must be from same card used in AUTH and OPS.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 server -> client (PKT_TYPE = FIN)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.

 * RECHARGE operation *
 OP_CODE = RECHARGE

 client -> server (PKT_TYPE = AUTH)
 - client sends Common Packet Header
 -- card_id and auth_code must be from a previously issued card
 -- status and transaction_id are unused (recommend to set to 0).
 server -> client (PKT_TYPE = AUTH)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the newly initiated transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 client -> server (PKT_TYPE = OPS)
 - client sends Common Packet Header followed by Recharge Data and associated Vendor Data
 -- card_id and auth_code must be from the card used during AUTH.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 -- cost should be <= balance on card
 -- purchase_id, vendor_id, vendor_location can be any random values
 -- vendor_type can be any value from VENDOR_TYPE enum
 server -> client (PKT_TYPE = OPS)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 client -> server (PKT_TYPE = FIN)
 - client sends Common Packet Header
 -- card_id and auth_code must be from same card used in AUTH and OPS.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 server -> client (PKT_TYPE = FIN)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.

 * BALANCE operation *
 OP_CODE = BALANCE

 client -> server (PKT_TYPE = AUTH)
 - client sends Common Packet Header
 -- card_id and auth_code must be from a previously issued card
 -- status and transaction_id are unused (recommend to set to 0).
 server -> client (PKT_TYPE = AUTH)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the newly initiated transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 client -> server (PKT_TYPE = OPS)
 - client sends Common Packet Header
 -- card_id and auth_code must be from the card used during AUTH.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 server -> client (PKT_TYPE = OPS)
 - server sends Common Packet Header followed by Balance Data
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 -- balance will be the balance of card matching card_id and auth_code.
 client -> server (PKT_TYPE = FIN)
 - client sends Common Packet Header
 -- card_id and auth_code must be from same card used in AUTH and OPS.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 server -> client (PKT_TYPE = FIN)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.

 * HISTORY operation *
 OP_CODE = HISTORY

 client -> server (PKT_TYPE = AUTH)
 - client sends Common Packet Header
 -- card_id and auth_code must be from a previously issued card
 -- status and transaction_id are unused (recommend to set to 0).
 server -> client (PKT_TYPE = AUTH)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the newly initiated transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 client -> server (PKT_TYPE = OPS)
 - client sends Common Packet Header followed by History Data
 -- card_id and auth_code must be from the card used during AUTH.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 -- count tells the server to send up to that many of the most recent transactions
 	that match the given card.
 server -> client (PKT_TYPE = OPS)
 - server sends Common Packet Header followed by History Data
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 -- count will be the number of transactions that the server will be sending.
 - server sends up to count Transaction Record + associated Data as follows:
 -- for all transactions, send Transaction Record followed by:
 --- if transaction OP_CODE==PURCHASE, send Purchase Data and associated Vendor Data
 --- if transaction OP_CODE==BALANCE, send Balance Data
 --- if transaction OP_CODE==ISSUE, send Issue Data
 --- if transaction OP_CODE==RECHARGE, send Recharge Data and associated Vendor Data
 --- if transaction OP_CODE==REFUND, send Refund Data
 --- if transaction OP_CODE==HISTORY, send History Data
 client -> server (PKT_TYPE = FIN)
 - client sends Common Packet Header
 -- card_id and auth_code must be from same card used in AUTH and OPS.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 server -> client (PKT_TYPE = FIN)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.

 * ISSUE operation *
 OP_CODE = ISSUE

 client -> server (PKT_TYPE = INIT)
 - client sends Common Packet Header
 -- card_id and auth_code are unused (recommend to set to 0).
 -- status and transaction_id are unused (recommend to set to 0).
 server -> client (PKT_TYPE = INIT)
 - server sends Common Packet Header
 -- card_id and auth_code will be those of the newly created card.
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the newly initiated transaction.
 client -> server (PKT_TYPE = FIN)
 - client sends Common Packet Header
 -- card_id and auth_code must be that provided by server in INIT.
 -- transaction_id must be that provided by server during INIT.
 -- status is unused (recommend to set to 0)
 server -> client (PKT_TYPE = FIN)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.

 * REFUND operation *
 OP_CODE = REFUND

 client -> server (PKT_TYPE = AUTH)
 - client sends Common Packet Header
 -- card_id and auth_code must be from a previously issued card
 -- status and transaction_id are unused (recommend to set to 0).
 server -> client (PKT_TYPE = AUTH)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the newly initiated transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 client -> server (PKT_TYPE = OPS)
 - client sends Common Packet Header followed by Refund Data
 -- card_id and auth_code must be from the card used during AUTH.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 -- purchase_id is the purchase_id from a previous purchase with this associated card.
 -- Purchase Data's transaction_id is the transaction_id from the previous purchase 
 	associated with purchase_id.
 server -> client (PKT_TYPE = OPS)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.
 client -> server (PKT_TYPE = FIN)
 - client sends Common Packet Header
 -- card_id and auth_code must be from same card used in AUTH and OPS.
 -- transaction_id must be that provided by server during AUTH
 -- status is unused (recommend to set to 0)
 server -> client (PKT_TYPE = FIN)
 - server sends Common Packet Header
 -- status will be set to a value from the STATUS enum.
 -- transaction_id will be set to the ID of the current transaction.
 -- card_id and auth_code will be the same as those provided to the server by the client.


** Transactions **

	FIRST_TRANSACTION_ID	= 191919

	* Transaction Record *
		OP_CODE op_code : 8;
		PKT_TYPE state : 8;
		STATUS status : 8;
		uint32_t card_id;
		uint32_t transaction_id;
		<Purchase|Balance|Issue|Recharge|Refund|History Data>;
		<Vendor Data if Purchase or Recharge Data in this transaction>

 Each operation results in a transaction record. 
 - The first transaction record has TRANSACTION_ID = FIRST_TRANSACTION_ID. 
 - Each subsequent record has TRANSACTION_ID = LATEST_TRANSACTION_ID + 1.
 - Each transaction record includes details for each operation.

** Multi-pass cards **

	FIRST_CARD_ID 			= 223344
	FIRST_CARD_AUTH_CODE	= 114466

	* Card Record *
		uint32_t card_id;
		uint32_t auth_code;
		uint32_t balance;

 The server issues and tracks Multi-pass cards, card authentication
 codes, and card balances.
 - The first multi-pass card has CARD_ID = FIRST_CARD_ID.
 - Each subsequent card has CARD_ID = LATEST_CARD_ID + 1.

 - The first card has AUTH_CODE = FIRST_CARD_AUTH_CODE.
 - Each subsequent card has LATEST_CARD_AUTH_CODE + 1.

 - The initial balance of a new card is provided by the client.

** Vendors **
 The PURCHASE and REFUND operations include vendor information.
 There are 7 valid types of vendors.
	* Types of Vendors *
	typedef enum {
		TRANSIT = 0,	// 0
		VENDING,		// 1
		CONVENIENCE,	// 2
		RESTAURANT,		// 3
		GAS,			// 4
		MOVIE,			// 5
		CAR 			// 6
	} VENDOR_TYPE;

 For each operation/transaction involving a vendor, the vendors'
 data is included.

	* Vendor Data *
	typedef struct vendor {
		uint32_t vendor_id;			
		VENDOR_TYPE vendor_type : 8;
		uint8_t vendor_location_sz;
		char * vendor_location;
	} vendor_t;

** Errors **
 Any errors in the server will cause the server to send to the client:
 1. Common Packet Header with status set to the error status value.
 2. Error Data with the message associated with error status value.
 3. Then the server will exit.

	* Error status codes *
	// this enum is used as 1 byte (0-255)
	typedef enum {
		OK = 0,
		ERRNO_MP_LIST_PUSH,		// Failed to add node to list
		ERRNO_MP_LIST_RM,		// Failed to rm node from list
		ERRNO_MP_ALLOC,			// Failed to allocate memory
		ERRNO_MP_DEALLOC,		// Failed to deallocate memory
		ERRNO_MP_PURCHASE_ISF,		// Insufficient Funds
		ERRNO_MP_RECHARGE_FULL,	// Recharge would case card balance to wrap
		ERRNO_MP_REFUND_FULL,	// Refund would cause card balance to wrap
		ERRNO_MP_NO_HISTORY,	// No matching transaction history in transaction list.
		ERRNO_MP_INVALID_OPCODE,	// Invalid Op_code
		ERRNO_MP_INVALID_P_TYPE,	// Invalid Packet Type
		ERRNO_MP_INVALID_V_TYPE,	// Invalid Vendor Type
		ERRNO_MP_NO_AUTH,		// Transaction did not complete AUTH step
		ERRNO_MP_NO_INIT,		// Transaction did not complete INIT step
		ERRNO_MP_NO_OPS,		// Transaction did not complete OPS step
		ERRNO_MP_NOT_FOUND,		// When the card or transaction is not in the list
		ERRNO_MP_INVALID_CARD,	// Card does not exist or is invalid
		ERRNO_MP_RECV,			// Failed to receive expected number of bytes
		ERRNO_MP_UNK			// Unknown error
	} STATUS;

	* Error Messages *
	// status -> message
	ERRNO_MP_LIST_PUSH 		-> "Failed to extend list."
	ERRNO_MP_LIST_RM 		-> "Failed to remove node from list."
	ERRNO_MP_ALLOC 			-> "Failed to allocate memory."
	ERRNO_MP_DEALLOC		-> "Failed to deallocate memory."
	ERRNO_MP_PURCHASE_ISF	-> "Insuffient funds for purchase."
	ERRNO_MP_RECHARGE_FULL	-> "Unable to recharge card. Balance near max."
	ERRNO_MP_REFUND_FULL	-> "Unable to refund card. Balance near max."
	ERRNO_MP_NO_HISTORY		-> "No matching transaction history."
	ERRNO_MP_INVALID_OPCODE	-> "Invalid OP_CODE."
	ERRNO_MP_INVALID_P_TYPE	-> "Invalid PKT_TYPE."
	ERRNO_MP_INVALID_V_TYPE	-> "Invalid VENDOR_TYPE."
	ERRNO_MP_NO_AUTH		-> "Transaction has not completed AUTH."
	ERRNO_MP_NO_INIT		-> "Transaction has not completed INIT."
	ERRNO_MP_NO_OPS			-> "Transaction has not completed OPS."
	ERRNO_MP_NOT_FOUND		-> "Card or transaction not found."
	ERRNO_MP_INVALID_CARD	-> "Invalid card or auth code."
	ERRNO_MP_RECV			-> "Receive failed."
	ERRNO_MP_UNK			-> "Unknown Error."


*/

#ifndef MULTIPASS_PROTOCOL_H
#define MULTIPASS_PROTOCOL_H

/* Static starting numbers */
#define FIRST_CARD_ID 			223344
#define FIRST_CARD_AUTH_CODE	114466
#define FIRST_TRANSACTION_ID	191919

/* Types of Vendors */
typedef enum {
	TRANSIT = 0,	// 0
	VENDING,		// 1
	CONVENIENCE,	// 2
	RESTAURANT,		// 3
	GAS,			// 4
	MOVIE,			// 5
	CAR 			// 6
} VENDOR_TYPE;

/* Types of Operations */
typedef enum {
	PURCHASE = 0,	// 0
	RECHARGE,		// 1
	BALANCE,		// 2
	HISTORY,		// 3
	ISSUE,			// 4
	REFUND			// 5
} OP_CODE;

/* Types of Packets */
typedef enum {
    INVALID = -1,
	INIT = 0,	// 0
	AUTH,		// 1
	OPS,		// 2
	FIN, 		// 3
    REFUNDED
} PKT_TYPE;

/* Types of Errors */
#define LIST_PUSH_MSG "Failed to extend list."
#define LIST_RM_MSG "Failed to remove node from list."
#define ALLOC_MSG "Failed to allocate memory."
#define DEALLOC_MSG "Failed to deallocate memory."
#define PURCHASE_ISF_MSG "Insuffient funds for purchase."
#define RECHARGE_FULL_MSG "Unable to recharge card. Balance near max."
#define REFUND_FULL_MSG "Unable to refund card. Balance near max."
#define NO_HISTORY_MSG "No matching transaction history."
#define INVALID_OPCODE_MSG "Invalid OP_CODE."
#define INVALID_PKT_TYPE_MSG "Invalid PKT_TYPE."
#define INVALID_V_TYPE_MSG "Invalid VENDOR_TYPE."
#define NO_AUTH_MSG "Transaction has not completed AUTH."
#define NO_INIT_MSG "Transaction has not completed INIT."
#define NO_OPS_MSG "Transaction has not completed OPS."
#define NOT_FOUND_MSG "Card or transaction not found."
#define INVALID_CARD_MSG "Invalid card or auth code."
#define RECV_FAIL_MSG "Receive failed."
#define UNK_ERROR_MSG "Unknown Error."

// this enum is used as 1 byte (0-255)
typedef enum {
	OK = 0,
	ERRNO_MP_LIST_PUSH,		// Failed to add node to list
	ERRNO_MP_LIST_RM,		// Failed to rm node from list
	ERRNO_MP_ALLOC,			// Failed to allocate memory
	ERRNO_MP_DEALLOC,		// Failed to deallocate memory
	ERRNO_MP_PURCHASE_ISF,		// Insufficient Funds
	ERRNO_MP_RECHARGE_FULL,	// Recharge would case card balance to wrap
	ERRNO_MP_REFUND_FULL,	// Refund would cause card balance to wrap
	ERRNO_MP_NO_HISTORY,	// No matching transaction history in transaction list.
	ERRNO_MP_INVALID_OPCODE,	// Invalid Op_code
	ERRNO_MP_INVALID_P_TYPE,	// Invalid Packet Type
	ERRNO_MP_INVALID_V_TYPE,	// Invalid Vendor Type
	ERRNO_MP_NO_AUTH,		// Transaction did not complete AUTH step
	ERRNO_MP_NO_INIT,		// Transaction did not complete INIT step
	ERRNO_MP_NO_OPS,		// Transaction did not complete OPS step
	ERRNO_MP_NOT_FOUND,		// When the card or transaction is not in the list
	ERRNO_MP_INVALID_CARD,	// Card does not exist or is invalid
	ERRNO_MP_RECV,			// Failed to receive expected number of bytes
	ERRNO_MP_UNK			// Unknown error
} STATUS;

/* 
  Headers and Data

  The Common Packet Header is sent between client and server
  for all communication.

  The Data values are used in client-server communications
  as well as in the transaction log.
*/

/* Common Packet Header */
typedef struct packet_head {
	uint32_t card_id;			// 4 bytes
	uint32_t auth_code;			// 4 bytes
	PKT_TYPE pkt_type : 8;		// 1 byte
	OP_CODE op_code : 8;		// 1 byte
	STATUS status : 8;			// 1 byte
	uint32_t transaction_id;	// 4 bytes
} __attribute__((__packed__)) packet_head_t;

/* Error Data */
typedef struct packet_data_error {
	uint32_t length;
	char msg[64];
} __attribute__((__packed__)) packet_data_error_t;

/* Vendor Data */
typedef struct vendor {
	uint32_t vendor_id;			
	VENDOR_TYPE vendor_type : 8;
	uint8_t vendor_location_sz;
	char vendor_location[];
} __attribute__((__packed__)) vendor_t;

/* Issue Data */
typedef struct packet_data_issue {
	uint32_t amount;
} __attribute__((__packed__)) packet_data_issue_t;

/* Balance Data */
typedef struct packet_data_balance {
	uint32_t balance;
} __attribute__((__packed__)) packet_data_balance_t;

/* History Data */
typedef struct packet_data_history {
	uint32_t count;
} __attribute__((__packed__)) packet_data_history_t;

/* Purchase Data */
typedef struct packet_data_purchase {
	uint32_t purchase_id;
	uint32_t cost;
	vendor_t v;
} __attribute__((__packed__)) packet_data_purchase_t;

/* Recharge Data */
typedef struct packet_data_recharge {
	uint32_t amount;
	vendor_t v;
} __attribute__((__packed__)) packet_data_recharge_t;

/* Refund Data */
typedef struct packet_data_refund {
	uint32_t purchase_id;
	uint32_t transaction_id;
} __attribute__((__packed__)) packet_data_refund_t;

typedef struct packet_data_transaction {
    OP_CODE op_code : 8;
    PKT_TYPE state : 8;
    STATUS status : 8;
    uint32_t card_id;
    uint32_t id;
} __attribute__((__packed__)) packet_data_transaction_t;

#endif
