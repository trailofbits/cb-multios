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

from generator.actions import Actions
from random import choice, randint
from os.path import dirname, abspath, join
import string
import sys


sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
from multipasssupport import MultiPassSupport

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def random_digits(a, b):
    chars = string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))


class MultiPass(Actions):

	INITIAL_CARD_AMOUNT = 1000
	
	DEBUG = False
	DEBUG_ISSUE = DEBUG or False
	DEBUG_BALANCE = DEBUG or False
	DEBUG_RECHARGE = DEBUG or False
	DEBUG_PURCHASE = DEBUG or False
	DEBUG_HISTORY = DEBUG or False
	DEBUG_REFUND = DEBUG or False
	MAX_UINT32 = 2 * sys.maxint + 1

	def start(self):
		self.state['mp'] = MultiPassSupport()

	def issue(self):
		if self.DEBUG_ISSUE:
			print('\nIssue')

		## INIT ##
		if self.DEBUG_ISSUE:
			print('INIT')
		# send packet header:
		# set: pkt_type INIT, op_code ISSUE, amount INITAL_CARD_AMOUNT
		msg_head = self.state['mp'].make_packet_head(pkt_type = 'INIT', op_code = 'ISSUE')
		if self.DEBUG_ISSUE:
			print(' write: msg_head: {0}'.format(msg_head))
		msg_issue = self.state['mp'].make_packet_data_issue(amount = self.INITIAL_CARD_AMOUNT)
		if self.DEBUG_ISSUE:
			print(' write: msg_issue: {0}'.format(msg_issue))
		msg = self.state['mp'].pack_packet_head(msg_head) + self.state['mp'].pack_packet_data_issue(msg_issue)
		self.write(msg)

		# build expected reply header, same as inital packet, except
		#  transaction_id, card_id and auth_code will be newly assigned
		new_card_id = self.state['mp'].get_next_card_id()
		new_auth_code = self.state['mp'].get_next_auth_code()
		new_transaction_id = self.state['mp'].get_next_transaction_id()
		msg_head = self.state['mp'].make_packet_head(
					card_id = new_card_id,
					auth_code = new_auth_code,
					pkt_type = 'INIT', 
					op_code = 'ISSUE',
					transaction_id = new_transaction_id)
		if self.DEBUG_ISSUE:
			print(' read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		# read reply packet header
		self.read(length=len(msg), expect=msg)

		# add card to C_LIST
		new_card = {'card_id': new_card_id,
					'auth_code': new_auth_code,
					'balance': self.INITIAL_CARD_AMOUNT}
		self.state['mp'].add_card(new_card)

		# add transaction to T_LIST
		new_issue = {'amount': self.INITIAL_CARD_AMOUNT}
		new_transaction = self.state['mp'].make_transaction(
											card_id = new_card_id, 
											state = 'INIT', 
											op_code = 'ISSUE', 
											transaction_id = new_transaction_id,
											details = new_issue)
		self.state['mp'].add_transaction(new_transaction)

		## FIN ##
		if self.DEBUG_ISSUE:
			print('\nFIN')
		msg_head = self.state['mp'].make_packet_head(
					card_id = new_card_id,
					auth_code = new_auth_code,
					pkt_type = 'FIN', 
					op_code = 'ISSUE',
					transaction_id = new_transaction_id)
		if self.DEBUG_ISSUE:
			print(' write then read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)
		self.read(length=len(msg), expect=msg)

		# update transaction to FIN
		self.state['mp'].update_transaction_state(new_transaction_id, 'FIN')


	def balance(self):
		if self.DEBUG_BALANCE:
			print('\nBalance')

		## AUTH ##
		# select a valid card
		if self.DEBUG_BALANCE:
			print('AUTH')
		card = self.state['mp'].get_random_card()
		if card == -1:
			return

		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'BALANCE')
		if self.DEBUG_BALANCE:
			print(' write: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)

		# build expected reply header, same as inital packet, except
		#  transaction_id will be newly assigned
		new_transaction_id = self.state['mp'].get_next_transaction_id()
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'BALANCE',
					transaction_id = new_transaction_id)
		if self.DEBUG_BALANCE:
			print(' read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		# read reply packet header
		self.read(length=len(msg), expect=msg)

		# add transaction to T_LIST
		new_transaction = self.state['mp'].make_transaction(
											card_id = card['card_id'], 
											state = 'AUTH', 
											op_code = 'BALANCE', 
											transaction_id = new_transaction_id)
		self.state['mp'].add_transaction(new_transaction)

		## OPS ##
		if self.DEBUG_BALANCE:
			print('\nOPS')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'OPS', 
					op_code = 'BALANCE',
					transaction_id = new_transaction_id)

		if self.DEBUG_BALANCE:
			print(' write: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)

		# expected reply header, same as sent packet
		if self.DEBUG_BALANCE:
			print(' read: msg_head: {0}'.format(msg_head))
		# read reply packet header
		self.read(length=len(msg), expect=msg)

		# read reply balance
		new_balance = self.state['mp'].make_packet_data_balance(card['balance'])

		if self.DEBUG_BALANCE:
			print(' read: new_balance: {0}'.format(new_balance))

		msg = self.state['mp'].pack_packet_data_balance(new_balance)
		self.read(length=len(msg), expect=msg)

		# set balance details
		self.state['mp'].update_transaction_details(new_transaction_id, new_balance)

		# update transaction to OPS
		self.state['mp'].update_transaction_state(new_transaction_id, 'OPS')

		## FIN ##
		if self.DEBUG_BALANCE:
			print('\nFIN')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'FIN', 
					op_code = 'BALANCE',
					transaction_id = new_transaction_id)
		if self.DEBUG_BALANCE:
			print(' write then read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)
		self.read(length=len(msg), expect=msg)

		# update transaction to FIN
		self.state['mp'].update_transaction_state(new_transaction_id, 'FIN')

	def recharge(self):
		if self.DEBUG_RECHARGE:
			print('\nRecharge')

		## AUTH ##
		# select a valid card
		if self.DEBUG_RECHARGE:
			print('AUTH')
		card = self.state['mp'].get_random_card()
		if card == -1:
			return

		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'RECHARGE')
		if self.DEBUG_RECHARGE:
			print(' write: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)

		# build expected reply header, same as inital packet, except
		#  transaction_id will be newly assigned
		new_transaction_id = self.state['mp'].get_next_transaction_id()
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'RECHARGE',
					transaction_id = new_transaction_id)
		if self.DEBUG_RECHARGE:
			print(' read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		# read reply packet header
		self.read(length=len(msg), expect=msg)

		# add transaction to T_LIST
		new_transaction = self.state['mp'].make_transaction(
											card_id = card['card_id'], 
											state = 'AUTH', 
											op_code = 'RECHARGE', 
											transaction_id = new_transaction_id)
		self.state['mp'].add_transaction(new_transaction)

		## OPS ##
		# handle case where card balance + new_recharge_amt > self.MAX_UINT32
		#	The service will return an ERRNO_MP_RECHARGE_FULL error and exit.

		if self.DEBUG_RECHARGE:
			print('\nOPS')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'OPS', 
					op_code = 'RECHARGE',
					transaction_id = new_transaction_id)

		if self.DEBUG_RECHARGE:
			print(' write: msg_head: {0}'.format(msg_head))

		# occasionally force balance to overflow maxint.
		if self.chance(0.0001):
			new_recharge_amt = self.MAX_UINT32
		else:
			istop = self.MAX_UINT32 - card['balance']
			if 1 >= istop:
				new_recharge_amt = randint(1, 12345)
			else:
				new_recharge_amt = randint(1, istop)

		FULL = False
		if self.MAX_UINT32 < card['balance'] + new_recharge_amt:
			FULL = True

		msg_recharge = self.state['mp'].make_packet_data_recharge(new_recharge_amt)
		if self.DEBUG_RECHARGE:
			print(' write: msg_recharge: {0}'.format(msg_recharge))
		msg = self.state['mp'].pack_packet_head(msg_head) + self.state['mp'].pack_packet_data_recharge(msg_recharge)
		self.write(msg)

		# expected reply header, same as inital packet head, unless recharge causes FULL
		# When card balance + new_recharge_amt > self.MAX_UINT32, the service will 
		#  return a ERRNO_MP_RECHARGE_FULL error and exit.

		if FULL == True:
			msg_head = self.state['mp'].make_packet_head(
						card_id = card['card_id'],
						auth_code = card['auth_code'],
						pkt_type = 'OPS', 
						op_code = 'RECHARGE',
						status = 'ERRNO_MP_RECHARGE_FULL',
						transaction_id = new_transaction_id)

		# expected reply header, same as inital packet head
		if self.DEBUG_RECHARGE:
			print(' read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		# read reply packet header
		self.read(length=len(msg), expect=msg)

		if FULL == True:
			# read error data
			msg_err = self.state['mp'].make_packet_data_error('ERRNO_MP_RECHARGE_FULL')
			if self.DEBUG_RECHARGE:
				print(' read: msg_err: {0}'.format(msg_err))
			msg = self.state['mp'].pack_packet_data_error(msg_err)
			self.read(length=len(msg), expect=msg)
			return -1

		# update balance of card
		self.state['mp'].card_recharge(card['card_id'], new_recharge_amt)

		# set recharge details
		self.state['mp'].update_transaction_details(new_transaction_id, msg_recharge)

		# update transaction to OPS
		self.state['mp'].update_transaction_state(new_transaction_id, 'OPS')

		## FIN ##
		if self.DEBUG_RECHARGE:
			print('\nFIN')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'FIN', 
					op_code = 'RECHARGE',
					transaction_id = new_transaction_id)
		if self.DEBUG_RECHARGE:
			print(' write then read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)
		self.read(length=len(msg), expect=msg)

		# update transaction to FIN
		self.state['mp'].update_transaction_state(new_transaction_id, 'FIN')


	def purchase(self):
		if self.DEBUG_PURCHASE:
			print('\nPurchase')

		## AUTH ##
		# select a valid card
		if self.DEBUG_PURCHASE:
			print('AUTH')
		card = self.state['mp'].get_random_card()
		if card == -1:
			return

		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'PURCHASE')
		if self.DEBUG_PURCHASE:
			print(' write: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)

		# build expected reply header, same as inital packet, except
		#  transaction_id will be newly assigned
		new_transaction_id = self.state['mp'].get_next_transaction_id()
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'PURCHASE',
					transaction_id = new_transaction_id)
		if self.DEBUG_PURCHASE:
			print(' read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		# read reply packet header
		self.read(length=len(msg), expect=msg)

		# add transaction to T_LIST
		new_transaction = self.state['mp'].make_transaction(
											card_id = card['card_id'], 
											state = 'AUTH', 
											op_code = 'PURCHASE', 
											transaction_id = new_transaction_id)
		self.state['mp'].add_transaction(new_transaction)

		## OPS ##

		if self.DEBUG_PURCHASE:
			print('\nOPS')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'OPS', 
					op_code = 'PURCHASE',
					transaction_id = new_transaction_id)

		if self.DEBUG_PURCHASE:
			print(' write: msg_head: {0}'.format(msg_head))

		# occassionally select a purchase amount greater than the card's balance
		if self.chance(0.001):
			new_purchase_amt = card['balance'] + 1
		else:
			new_purchase_amt = randint(1, card['balance'] + 1)
		msg_purchase = self.state['mp'].make_packet_data_purchase(new_purchase_amt)
		if self.DEBUG_PURCHASE:
			print(' write: msg_purchase: {0}'.format(msg_purchase))
		msg = self.state['mp'].pack_packet_head(msg_head) + self.state['mp'].pack_packet_data_purchase(msg_purchase)
		self.write(msg)

		# expected reply header, same as inital packet head, unless purchase causes ISF
		# When card balance < new_purchase_amt, the service will return an ISF error and exit.

		ISF = False
		if new_purchase_amt > card['balance']:
			ISF = True
			msg_head = self.state['mp'].make_packet_head(
						card_id = card['card_id'],
						auth_code = card['auth_code'],
						pkt_type = 'OPS', 
						op_code = 'PURCHASE',
						status = 'ERRNO_MP_PURCHASE_ISF',
						transaction_id = new_transaction_id)

		if self.DEBUG_PURCHASE:
			print(' read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		# read reply packet header
		self.read(length=len(msg), expect=msg)

		if ISF == True:
			# read error data
			msg_err = self.state['mp'].make_packet_data_error('ERRNO_MP_PURCHASE_ISF')
			if self.DEBUG_PURCHASE:
				print(' read: msg_err: {0}'.format(msg_err))
			msg = self.state['mp'].pack_packet_data_error(msg_err)
			self.read(length=len(msg), expect=msg)
			return -1

		# update balance of card
		self.state['mp'].card_purchase(card['card_id'], new_purchase_amt)

		# set recharge details
		self.state['mp'].update_transaction_details(new_transaction_id, msg_purchase)

		# update transaction to OPS
		self.state['mp'].update_transaction_state(new_transaction_id, 'OPS')

		## FIN ##
		if self.DEBUG_PURCHASE:
			print('\nFIN')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'FIN', 
					op_code = 'PURCHASE',
					transaction_id = new_transaction_id)
		if self.DEBUG_PURCHASE:
			print(' write then read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)
		self.read(length=len(msg), expect=msg)

		# update transaction to FIN
		self.state['mp'].update_transaction_state(new_transaction_id, 'FIN')

	def history(self):
		if self.DEBUG_HISTORY:
			print('\nHistory')

		## AUTH ##
		# select a valid card
		if self.DEBUG_HISTORY:
			print('AUTH')
		card = self.state['mp'].get_random_card()
		if card == -1:
			return

		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'HISTORY')
		if self.DEBUG_HISTORY:
			print(' write: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)

		# build expected reply header, same as inital packet, except
		#  transaction_id will be newly assigned
		new_transaction_id = self.state['mp'].get_next_transaction_id()
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'HISTORY',
					transaction_id = new_transaction_id)
		if self.DEBUG_HISTORY:
			print(' read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		# read reply packet header
		self.read(length=len(msg), expect=msg)

		# add transaction to T_LIST
		new_transaction = self.state['mp'].make_transaction(
											card_id = card['card_id'], 
											state = 'AUTH', 
											op_code = 'HISTORY', 
											transaction_id = new_transaction_id)
		self.state['mp'].add_transaction(new_transaction)

		## OPS ##
		if self.DEBUG_HISTORY:
			print('\nOPS')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'OPS', 
					op_code = 'HISTORY',
					transaction_id = new_transaction_id)

		if self.DEBUG_HISTORY:
			print(' write: msg_head: {0}'.format(msg_head))
		history_cnt = randint(1, 20)
		msg_history = self.state['mp'].make_packet_data_history(history_cnt)
		if self.DEBUG_HISTORY:
			print(' write: msg_history: {0}'.format(msg_history))

		msg = self.state['mp'].pack_packet_head(msg_head) + self.state['mp'].pack_packet_data_history(msg_history)	
		self.write(msg)

		# set history details
		self.state['mp'].update_transaction_details(new_transaction_id, msg_history)

		# update transaction to OPS
		self.state['mp'].update_transaction_state(new_transaction_id, 'OPS')

		# expected reply header, same as sent packet msg_head
		if self.DEBUG_HISTORY:
			print(' read: msg_head: {0}'.format(msg_head))
		# read reply packet header and reply history count (the number of historical records that will be sent)
		history_cnt_avail = self.state['mp'].get_history_count_avail(card['card_id'], history_cnt)
		msg_history = self.state['mp'].make_packet_data_history(history_cnt_avail)

		if self.DEBUG_HISTORY:
			print(' read: msg_history: {0}'.format(msg_history))

		msg = self.state['mp'].pack_packet_head(msg_head) + self.state['mp'].pack_packet_data_history(msg_history)
		self.read(length=len(msg), expect=msg)


		# read history_cnt_avail historical transactions and details
		# TODO: if history_cnt_avail < 0, server will return ERRNO_MP_NO_HISTORY and exit.
		for tr in self.state['mp'].get_historical_transactions_iter(card['card_id'], history_cnt_avail):
			# read transaction header (minus details)
			if self.DEBUG_HISTORY:
				print(' read: tr and details: {0}'.format(tr))

			msg = self.state['mp'].pack_transaction_head(tr)
			self.read(length=len(msg), expect=msg)

			# read transaction details
			msg = self.state['mp'].pack_transaction_details(tr)
			if msg == -1:
				return msg
			self.read(length=len(msg), expect=msg)

		## FIN ##
		if self.DEBUG_HISTORY:
			print('\nFIN')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'FIN', 
					op_code = 'HISTORY',
					transaction_id = new_transaction_id)
		if self.DEBUG_HISTORY:
			print(' write then read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)
		self.read(length=len(msg), expect=msg)

		# update transaction to FIN
		self.state['mp'].update_transaction_state(new_transaction_id, 'FIN')

	def refund(self):
		if self.DEBUG_REFUND:
			print('\nRefund')

		## AUTH ##
		# select a valid card that was used to make a purchase
		if self.DEBUG_REFUND:
			print('AUTH')
		card = self.state['mp'].get_random_card_with_purchase()
		# if no cards made a purchase, exit or use a valid card anyway
		if card == {}:
			if self.DEBUG_REFUND:
				print(' no cards made a purchase.')
			if self.chance(0.001):
				card = self.state['mp'].get_random_card()
			else:
				return

		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'REFUND')
		if self.DEBUG_REFUND:
			print(' write: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)

		# build expected reply header, same as inital packet, except
		#  transaction_id will be newly assigned
		new_transaction_id = self.state['mp'].get_next_transaction_id()
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'AUTH', 
					op_code = 'REFUND',
					transaction_id = new_transaction_id)
		if self.DEBUG_REFUND:
			print(' read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		# read reply packet header
		self.read(length=len(msg), expect=msg)

		# add transaction to T_LIST
		new_transaction = self.state['mp'].make_transaction(
											card_id = card['card_id'], 
											state = 'AUTH', 
											op_code = 'REFUND', 
											transaction_id = new_transaction_id)
		self.state['mp'].add_transaction(new_transaction)

		## OPS ##
		if self.DEBUG_REFUND:
			print('\nOPS')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'OPS', 
					op_code = 'REFUND',
					transaction_id = new_transaction_id)

		if self.DEBUG_REFUND:
			print(' write: msg_head: {0}'.format(msg_head))
		NOT_FOUND = False
		msg_refund = self.state['mp'].get_random_refund_data_by_card(card)

		if msg_refund == {}:
			if self.chance(0.001):
				msg_refund = self.state['mp'].get_bogus_refund_data_by_card(card)
				NOT_FOUND = True

		if msg_refund == {}:
			return -1

		FULL = False
		if self.MAX_UINT32 < card['balance'] + self.state['mp'].get_purchase_cost_for_transaction(msg_refund['transaction_id']):
			FULL = True

		if self.DEBUG_REFUND:
			print(' write: msg_refund: {0}'.format(msg_refund))

		msg = self.state['mp'].pack_packet_head(msg_head) + self.state['mp'].pack_packet_data_refund(msg_refund)	
		self.write(msg)

		# set history details
		self.state['mp'].update_transaction_details(new_transaction_id, msg_refund)

		# update transaction to OPS
		self.state['mp'].update_transaction_state(new_transaction_id, 'OPS')

		# expected reply header, same as inital packet head, unless refund causes NOT_FOUND
		# When purchase_id doesn't match transaction_id, the service will return an NOT_FOUND error and exit.

		if NOT_FOUND == True:
			msg_head = self.state['mp'].make_packet_head(
						card_id = card['card_id'],
						auth_code = card['auth_code'],
						pkt_type = 'OPS', 
						op_code = 'REFUND',
						status = 'ERRNO_MP_NOT_FOUND',
						transaction_id = new_transaction_id)
		elif FULL == True:
			msg_head = self.state['mp'].make_packet_head(
						card_id = card['card_id'],
						auth_code = card['auth_code'],
						pkt_type = 'OPS', 
						op_code = 'REFUND',
						status = 'ERRNO_MP_REFUND_FULL',
						transaction_id = new_transaction_id)

		if self.DEBUG_REFUND:
			print(' read: msg_head: {0}'.format(msg_head))

		msg = self.state['mp'].pack_packet_head(msg_head)
		self.read(length=len(msg), expect=msg)

		if NOT_FOUND == True:
			# read error data
			msg_err = self.state['mp'].make_packet_data_error('ERRNO_MP_NOT_FOUND')
			msg = self.state['mp'].pack_packet_data_error(msg_err)
			self.read(length=len(msg), expect=msg)
			return -1
		elif FULL == True:
			# read error data
			msg_err = self.state['mp'].make_packet_data_error('ERRNO_MP_REFUND_FULL')
			msg = self.state['mp'].pack_packet_data_error(msg_err)
			self.read(length=len(msg), expect=msg)
			return -1

		# refund cost to card
		self.state['mp'].refund_purchase_to_card(msg_refund)

		# destroy refunded transaction
		self.state['mp'].delete_refunded_purchase_transaction(msg_refund)


		## FIN ##
		if self.DEBUG_REFUND:
			print('\nFIN')
		msg_head = self.state['mp'].make_packet_head(
					card_id = card['card_id'],
					auth_code = card['auth_code'],
					pkt_type = 'FIN', 
					op_code = 'REFUND',
					transaction_id = new_transaction_id)
		if self.DEBUG_REFUND:
			print(' write then read: msg_head: {0}'.format(msg_head))
		msg = self.state['mp'].pack_packet_head(msg_head)
		self.write(msg)
		self.read(length=len(msg), expect=msg)

		# update transaction to FIN
		self.state['mp'].update_transaction_state(new_transaction_id, 'FIN')


