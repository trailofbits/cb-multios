#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

import struct
import string
from random import choice, randint
from os.path import join

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def random_digits(a, b):
    chars = string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))


class MultiPassSupport(object):

	FIRST_CARD_ID = 223344
	FIRST_CARD_AUTH_CODE = 114466
	FIRST_TRANSACTION_ID = 191919

	VENDOR_TYPE = {
		"TRANSIT" : 0,
		"VENDING" : 1,
		"CONVENIENCE" : 2,
		"RESTAURANT" : 3,
		"GAS" : 4,
		"MOVIE" : 5,
		"CAR" : 6
	}

	OP_CODE = {
		"PURCHASE" : 0,
		"RECHARGE" : 1,
		"BALANCE" : 2,
		"HISTORY" : 3,
		"ISSUE" : 4,
		"REFUND" : 5
	}

	PKT_TYPE = {
		"INIT" : 0,
		"AUTH" : 1,
		"OPS" : 2,
		"FIN" : 3
	}

	STATUS = {
		"OK" : 0,
		"ERRNO_MP_LIST_PUSH" : 1,
		"ERRNO_MP_LIST_RM" : 2,
		"ERRNO_MP_ALLOC" : 3,
		"ERRNO_MP_DEALLOC" : 4,
		"ERRNO_MP_PURCHASE_ISF" : 5,
		"ERRNO_MP_RECHARGE_FULL" : 6,
		"ERRNO_MP_REFUND_FULL" : 7,
		"ERRNO_MP_NO_HISTORY" : 8,
		"ERRNO_MP_INVALID_OPCODE" : 9,
		"ERRNO_MP_INVALID_P_TYPE" : 10,
		"ERRNO_MP_INVALID_V_TYPE" : 11,
		"ERRNO_MP_NO_AUTH" : 12,
		"ERRNO_MP_NO_INIT" : 13,
		"ERRNO_MP_NO_OPS" : 14,
		"ERRNO_MP_NOT_FOUND" : 15,
		"ERRNO_MP_INVALID_CARD" : 16,
		"ERRNO_MP_RECV" : 17,
		"ERRNO_MP_UNK" : 18,
	}

	ERR_STRING = {
		"OK" : '',
		"ERRNO_MP_LIST_PUSH" : "Failed to extend list.",
		"ERRNO_MP_LIST_RM" : "Failed to remove node from list.",
		"ERRNO_MP_ALLOC" : "Failed to allocate memory.",
		"ERRNO_MP_DEALLOC" : "Failed to deallocate memory.",
		"ERRNO_MP_PURCHASE_ISF" : "Insuffient funds for purchase.",
		"ERRNO_MP_RECHARGE_FULL" : "Unable to recharge card. Balance near max.",
		"ERRNO_MP_REFUND_FULL" : "Unable to refund card. Balance near max.",
		"ERRNO_MP_NO_HISTORY" : "No matching transaction history.",
		"ERRNO_MP_INVALID_OPCODE" : "Invalid OP_CODE.",
		"ERRNO_MP_INVALID_P_TYPE" : "Invalid PKT_TYPE.",
		"ERRNO_MP_INVALID_V_TYPE" : "Invalid VENDOR_TYPE.",
		"ERRNO_MP_NO_AUTH" : "Transaction has not completed AUTH.",
		"ERRNO_MP_NO_INIT" : "Transaction has not completed INIT.",
		"ERRNO_MP_NO_OPS" : "Transaction has not completed OPS.",
		"ERRNO_MP_NOT_FOUND" : "Card or transaction not found.",
		"ERRNO_MP_INVALID_CARD" : "Invalid card or auth code.",
		"ERRNO_MP_RECV" : "Receive failed.",
		"ERRNO_MP_UNK" : "Unknown Error.",
	}

	def __init__(self):
		self.T_LIST = [] # transaction list
		self.C_LIST = [] # card list
		self.V_LIST = [] # vendor list
		self._gen_vendors()
		self.NEXT_TRANSACTION_ID = self.FIRST_TRANSACTION_ID
		self.NEXT_CARD_ID = self.FIRST_CARD_ID
		self.NEXT_CARD_AUTH_CODE = self.FIRST_CARD_AUTH_CODE

	def _gen_vendors(self):
		'''
		typedef struct vendor {
			uint32_t vendor_id;			
			VENDOR_TYPE vendor_type : 8;
			uint8_t vendor_location_sz;
			char * vendor_location;
		} vendor_t;
		'''
		for name, val in self.VENDOR_TYPE.iteritems():
			# 0 < vls < 256
			vls = randint(10, 255)

			new_vendor = {
				'vendor_id': randint(0, 999999), 
				'vendor_type': val,
				'vendor_location_sz': vls, 
				'vendor_location': random_string(vls, vls)
			}

			self.V_LIST.append(new_vendor)

	def get_card_count(self):
		return len(self.C_LIST)

	def get_transaction_count(self):
		return len(self.T_LIST)

	def get_next_card_id(self):
		return self.NEXT_CARD_ID

	def get_next_auth_code(self):
		return self.NEXT_CARD_AUTH_CODE

	def get_next_transaction_id(self):
		return self.NEXT_TRANSACTION_ID

	def add_card(self, card):
		self.C_LIST.append(card)
		self.NEXT_CARD_ID += 1
		self.NEXT_CARD_AUTH_CODE += 1

	def get_card_idx_by_id(self, card_id):
		for idx in range(0, self.get_card_count()):
			if self.C_LIST[idx]['card_id'] == card_id:
				return idx
		return -1

	def get_card_by_id(self, card_id):
		return self.C_LIST[self.get_card_idx_by_id(card_id)]

	def add_transaction(self, transaction):
		self.T_LIST.append(transaction)
		self.NEXT_TRANSACTION_ID += 1

	def get_transaction_idx_by_id(self, transaction_id):
		for idx in range(0, self.get_transaction_count()):
			if self.T_LIST[idx]['transaction_id'] == transaction_id:
				return idx
		return -1

	def update_transaction_state(self, transaction_id, state):
		tr_idx = self.get_transaction_idx_by_id(transaction_id)
		self.T_LIST[tr_idx]['state'] = self.PKT_TYPE[state]

	def update_transaction_details(self, transaction_id, details):
		tr_idx = self.get_transaction_idx_by_id(transaction_id)
		self.T_LIST[tr_idx]['details'] = details

	def get_random_card(self):
		cnt = self.get_card_count()
		if cnt == 0:
			return -1
		else:
			rand_idx = randint(0, cnt - 1)
			return self.C_LIST[rand_idx]

	def get_list_of_cards_with_purchases(self):
		'''
		Get the list of card ids that were used to make a purchase.
		Return [] if none were used to make a purchase.
		'''
		cards = []
		for transaction in self.T_LIST:
			if transaction['op_code'] == self.OP_CODE['PURCHASE']:
				cards.append(transaction['card_id'])

		return cards

	def get_random_card_with_purchase(self):
		'''
		Get a random card that was used to make a purchase.
		Return {} if none were used to make a purchase.
		'''
		# from transaction history, get list of card ids used to make a purchase
		cards_id_list = self.get_list_of_cards_with_purchases()

		# if none, return {}
		if len(cards_id_list) == 0:
			return {}
		# else, select a random card from that list
		else:
			rand_idx = randint(0, len(cards_id_list) - 1)
			return self.get_card_by_id(cards_id_list[rand_idx])

	def get_random_refund_data_by_card(self, card):
		'''
		Get list of purchases made by this card and return a 
		refund data for a random purchase in that list.
		If no purchases were made by this card, return {}
		'''
		refund_list = []
		for tr in self.T_LIST:

			if (tr['op_code'] == self.OP_CODE['PURCHASE']) and (tr['card_id'] == card['card_id']):
				p_id = tr['details']['purchase_id']
				t_id = tr['transaction_id']
				refund_list.append(self.make_packet_data_refund(p_id, t_id))

		if len(refund_list) == 0:
			return {}
		else:
			rand_idx = randint(0, len(refund_list) -1)
			return refund_list[rand_idx]

	def get_bogus_refund_data_by_card(self, card):
		refund_list = []
		for tr in self.T_LIST:

			if (tr['op_code'] != self.OP_CODE['PURCHASE']) and (tr['card_id'] == card['card_id']):
				p_id = 100
				t_id = tr['transaction_id']
				refund_list.append(self.make_packet_data_refund(p_id, t_id))
				break

		if len(refund_list) == 0:
			return {}
		else:
			return refund_list[0]

	def get_purchase_cost_for_transaction(self, transaction_id):
		tr_idx = self.get_transaction_idx_by_id(transaction_id)
		return self.T_LIST[tr_idx]['details']['cost']

	def refund_purchase_to_card(self, msg_refund):
		# use msg_refund to find purchase transaction
		tr_idx = self.get_transaction_idx_by_id(msg_refund['transaction_id'])

		# find card and cost used in purchase transaction
		card_id = self.T_LIST[tr_idx]['card_id']
		cost = self.T_LIST[tr_idx]['details']['cost']

		# refund purchase cost to card
		self.card_recharge(card_id, cost)

	def delete_refunded_purchase_transaction(self, msg_refund):
		# use msg_refund to find purchase transaction
		tr_idx = self.get_transaction_idx_by_id(msg_refund['transaction_id'])

		# delete transaction from T_LIST
		del self.T_LIST[tr_idx]

	def	delete_refunded_purchase_details(self, msg_refund):
		# use msg_refund to find purchase transaction
		tr_idx = self.get_transaction_idx_by_id(msg_refund['transaction_id'])

		# delete transaction from T_LIST
		self.T_LIST[tr_idx]['details'] = {}

	def card_recharge(self, card_id, recharge_amt):
		card_idx = self.get_card_idx_by_id(card_id)
		self.C_LIST[card_idx]['balance'] += recharge_amt

	def card_purchase(self, card_id, purchase_amt):
		card_idx = self.get_card_idx_by_id(card_id)
		self.C_LIST[card_idx]['balance'] -= purchase_amt

	def get_history_count_avail(self, card_id, history_cnt):
		'''
		starting from the end of T_LIST count number of transactions 
		  for this card_id up to a max of history_cnt
		'''

		# there should never be an empty T_LIST during an OPS
		t_count = len(self.T_LIST)
		if t_count == 0:
			return -1

		count_avail = 0
		for transaction in reversed(self.T_LIST):
			# print(' tr: {0}'.format(transaction))
			if count_avail >= history_cnt:
				break
			if transaction['card_id'] == card_id:
				# print(' t_id: {0}, c_id: {1}'.format(transaction['transaction_id'], transaction['card_id']))
				count_avail += 1

		return count_avail

	def get_historical_transactions_iter(self, card_id, history_cnt_avail):
		'''
		Return iterator over the list of historical transactions 
		  for this card_id up to history_cnt_avail transactions.
		'''
		count_avail = 0
		for transaction in reversed(self.T_LIST):
			if count_avail >= history_cnt_avail:
				return
			if transaction['card_id'] == card_id:
				# print(' t_id: {0}, c_id: {1}'.format(transaction['transaction_id'], transaction['card_id']))
				yield transaction
				count_avail += 1

	def make_transaction(self, 
							card_id = 0,
							state = 'INIT', op_code = 'ISSUE', 
							status = 'OK', transaction_id = 0,
							details = {}):
		'''
		typedef struct transaction {
			OP_CODE op_code : 8;
			PKT_TYPE state : 8;
			STATUS status : 8;
			uint32_t card_id;
			uint32_t transaction_id;
			void * details;
		} transaction_t;
		'''
		new_tr = {}
		new_tr['card_id'] = card_id
		new_tr['state'] = self.PKT_TYPE[state]
		new_tr['op_code'] = self.OP_CODE[op_code]
		new_tr['status'] = self.STATUS[status]
		new_tr['transaction_id'] = transaction_id
		new_tr['details'] = details
		return new_tr


	def pack_transaction_head(self, tr_head_data):
		tr_head_data_fmt = 'BBBII'
		# ignore tr details
		return struct.pack(tr_head_data_fmt,
							tr_head_data['op_code'],
							tr_head_data['state'],
							tr_head_data['status'],
							tr_head_data['card_id'],
							tr_head_data['transaction_id'])

	def pack_transaction_details(self, tr):
		'''
		Pack and return transaction details based on op_code
		'''
		details = tr['details']
		if details == {}:
			return -1

		if tr['op_code'] == self.OP_CODE['PURCHASE']:
			return self.pack_packet_data_purchase(details)

		elif tr['op_code'] == self.OP_CODE['RECHARGE']:
			return self.pack_packet_data_recharge(details)

		elif tr['op_code'] == self.OP_CODE['BALANCE']:
			return self.pack_packet_data_balance(details)

		elif tr['op_code'] == self.OP_CODE['HISTORY']:
			return self.pack_packet_data_history(details)

		elif tr['op_code'] == self.OP_CODE['ISSUE']:
			return self.pack_packet_data_issue(details)

		elif tr['op_code'] == self.OP_CODE['REFUND']:
			return self.pack_packet_data_refund(details)

		else:
			return -1

	def make_packet_head(self, 
							card_id = 0, auth_code = 0,
							pkt_type = 'INIT', op_code = 'ISSUE', 
							status = 'OK', transaction_id = 0,
							op_code_int = False):
		'''
		typedef struct packet_head {
			uint32_t card_id;			// 4 bytes
			uint32_t auth_code;			// 4 bytes
			PKT_TYPE pkt_type : 8;		// 1 byte
			OP_CODE op_code : 8;		// 1 byte
			STATUS status : 8;			// 1 byte
			uint32_t transaction_id;	// 4 bytes
		} packet_head_t;
		'''
 
		pkt_head = {}
		pkt_head['card_id'] = card_id
		pkt_head['auth_code'] = auth_code
		pkt_head['pkt_type'] = self.PKT_TYPE[pkt_type]
		if True == op_code_int:
			pkt_head['op_code'] = op_code
		else:
			pkt_head['op_code'] = self.OP_CODE[op_code]
		pkt_head['status'] = self.STATUS[status]
		pkt_head['transaction_id'] = transaction_id
		return pkt_head

	def make_packet_head_custom(self, 
							card_id = 0, auth_code = 0,
							pkt_type = 0, op_code = 0, 
							status = 0, transaction_id = 0):
		'''
		typedef struct packet_head {
			uint32_t card_id;			// 4 bytes
			uint32_t auth_code;			// 4 bytes
			PKT_TYPE pkt_type : 8;		// 1 byte
			OP_CODE op_code : 8;		// 1 byte
			STATUS status : 8;			// 1 byte
			uint32_t transaction_id;	// 4 bytes
		} packet_head_t;
		'''
 
		pkt_head = {}
		pkt_head['card_id'] = card_id
		pkt_head['auth_code'] = auth_code
		pkt_head['pkt_type'] = pkt_type
		pkt_head['op_code'] = op_code
		pkt_head['status'] = status
		pkt_head['transaction_id'] = transaction_id
		return pkt_head

	def pack_packet_head(self, packet_head):
		packed_head_fmt = 'IIBBBI'
		return struct.pack(packed_head_fmt,
							packet_head['card_id'],
							packet_head['auth_code'],
							packet_head['pkt_type'],
							packet_head['op_code'],
							packet_head['status'],
							packet_head['transaction_id'])

	def make_packet_data_issue(self, amount):
		'''
		typedef struct packet_data_issue {
			uint32_t amount;
		} packet_data_issue_t;
		'''
		return {'amount': amount}

	def pack_packet_data_issue(self, issue_data):
		issue_data_fmt = 'I'
		return struct.pack(issue_data_fmt, issue_data['amount'])

	def make_packet_data_balance(self, balance):
		'''
		typedef struct packet_data_balance {
			uint32_t balance;
		} packet_data_balance_t;
		'''
		return {'balance': balance}

	def pack_packet_data_balance(self, balance_data):
		balance_data_fmt = 'I'
		return struct.pack(balance_data_fmt, balance_data['balance'])

	def make_packet_data_recharge(self, amount):
		'''
		typedef struct packet_data_recharge {
			uint32_t amount;
			vendor_t v;
		} packet_data_recharge_t;
		typedef struct vendor {
			uint32_t vendor_id;			
			VENDOR_TYPE vendor_type : 8;
			uint8_t vendor_location_sz;
			char * vendor_location;
		} vendor_t;
		'''
		# select a random vendor from V_LIST
		vendor_idx = randint(0, len(self.V_LIST) - 1)
		return {'amount': amount, 
				'vendor_id': self.V_LIST[vendor_idx]['vendor_id'], 
				'vendor_type': self.V_LIST[vendor_idx]['vendor_type'],
				'vendor_location_sz': self.V_LIST[vendor_idx]['vendor_location_sz'], 
				'vendor_location': self.V_LIST[vendor_idx]['vendor_location']
				}


	def pack_packet_data_recharge(self, recharge_data):
		recharge_data_fmt = 'IIBB' + str(recharge_data['vendor_location_sz']) + 's'

		return struct.pack(recharge_data_fmt, 
							recharge_data['amount'],
							recharge_data['vendor_id'],
							recharge_data['vendor_type'],
							recharge_data['vendor_location_sz'],
							recharge_data['vendor_location']
							)

	def make_packet_data_purchase(self, cost):
		'''
		typedef struct packet_data_purchase {
			uint32_t purchase_id;
			uint32_t cost;
			vendor_t v;
		} packet_data_purchase_t;
		typedef struct vendor {
			uint32_t vendor_id;			
			VENDOR_TYPE vendor_type : 8;
			uint8_t vendor_location_sz;
			char * vendor_location;
		} vendor_t;
		'''
		# select a random vendor from V_LIST
		vendor_idx = randint(0, len(self.V_LIST) - 1)
		return {'purchase_id': randint(0, 999999),
				'cost': cost, 
				'vendor_id': self.V_LIST[vendor_idx]['vendor_id'], 
				'vendor_type': self.V_LIST[vendor_idx]['vendor_type'],
				'vendor_location_sz': self.V_LIST[vendor_idx]['vendor_location_sz'], 
				'vendor_location': self.V_LIST[vendor_idx]['vendor_location']
				}

	def pack_packet_data_purchase(self, purchase_data):
		purchase_data_fmt = 'IIIBB' + str(purchase_data['vendor_location_sz']) + 's'

		return struct.pack(purchase_data_fmt, 
							purchase_data['purchase_id'],
							purchase_data['cost'],
							purchase_data['vendor_id'],
							purchase_data['vendor_type'],
							purchase_data['vendor_location_sz'],
							purchase_data['vendor_location']
							)

	def make_packet_data_history(self, count):
		'''
		typedef struct packet_data_history {
			uint32_t count;
		} packet_data_history_t;
		'''
		return {'count': count}

	def pack_packet_data_history(self, history_data):
		history_data_fmt = 'I'
		return struct.pack(history_data_fmt, history_data['count'])

	def make_packet_data_refund(self, purchase_id, transaction_id):
		'''
		typedef struct packet_data_refund {
			uint32_t purchase_id;
			uint32_t transaction_id;
		} packet_data_refund_t;
		'''
		return {'purchase_id': purchase_id, 'transaction_id': transaction_id}

	def pack_packet_data_refund(self, refund_data):
		refund_data_fmt = 'II'
		return struct.pack(refund_data_fmt,
							refund_data['purchase_id'],
							refund_data['transaction_id'])

	def make_packet_data_error(self, err_code):
		'''
		typedef struct packet_data_error {
			uint32_t length;
			char * msg;
		} packet_data_error_t;
		'''
		err_msg = self.ERR_STRING[err_code]
		return {'length': len(err_msg), 'msg': err_msg}

	def pack_packet_data_error(self, error_data):
		error_data_fmt = 'I' + str(error_data['length']) + 's'
		return struct.pack(error_data_fmt, error_data['length'], error_data['msg'])
