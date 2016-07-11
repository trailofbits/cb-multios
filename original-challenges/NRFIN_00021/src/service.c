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
#include <libcgc.h>
#include "libc.h"
#include "service.h"

int nextRecord(Record* record) {
	int bytesRead = 0;
	int ret;

	bytesRead = recv(STDIN, (char *)record, sizeof(Record));
	if(bytesRead < 0)
		_terminate(RECEIVE_ERROR);

	if(record->x == BALANCE_RECORD)
		return BALANCE_RECORD;

	if(record->x > 0 && record->y > 0 && record->x < 0xFFFF)
		return STOCK_RECORD;

	return NO_MORE_RECORDS;

}

float squareRoot(float value) {
	float low, high, mid, oldmid, midsqr;

	low = 0;
	high = mid = value;
	oldmid = -1;

	while (fabs(oldmid - mid) >= 0.001) {
		oldmid = mid;

		mid = (high + low) / 2;
		midsqr = mid * mid;

		if (mid * mid > value) {
			high = mid;
		} else {
			low = mid;
		}
	}

	return mid;
}

void addRecordToDataset(Dataset* dataset, Record record) {

	float priceRelative, oldMean;

	dataset->sampleSize++;

	priceRelative = (float)record.x/record.y;
	oldMean = dataset->mean;
	dataset->mean = oldMean + (priceRelative - oldMean) / dataset->sampleSize;

	dataset->Q = dataset->Q + (priceRelative - oldMean) * (priceRelative - dataset->mean);
	dataset->variance = dataset->Q / dataset->sampleSize;

	dataset->stdDev = squareRoot(dataset->variance);
	

}

Stock* getNextFreeEntry(Portfolio* portfolio) {

	int entry;
	for(entry=0; entry<portfolio->numEntries; entry++) {

		Stock* stock; 
		stock = &portfolio->stocks[entry];
		if(stock->symbol == 0) {
			return stock;
		}
	}

	int ret, oldNumEntries;
	Stock* oldStocks;
	oldStocks = portfolio->stocks;
	oldNumEntries = portfolio->numEntries;
#ifdef PATCHED
	// The first integer overflow, will set numEntries to 0, which will cause allocate to error and a _terminate to occur.
	portfolio->numEntries = oldNumEntries*16;
#else
	// Causes numEntries to be set to 65, which will cause a Segmentation Fault when entry = 66 on the for loop.
	portfolio->numEntries = oldNumEntries*64 + 1;
#endif
	ret = allocate(sizeof(Stock)*portfolio->numEntries, 0, (void **) &portfolio->stocks);
	if(ret != 0)
		_terminate(ALLOCATE_ERROR);

	for(entry=0; entry<oldNumEntries; entry++) {
		portfolio->stocks[entry].symbol = oldStocks[entry].symbol;
		portfolio->stocks[entry].purchasedPrice = oldStocks[entry].purchasedPrice; 
		portfolio->stocks[entry].currentPrice = oldStocks[entry].currentPrice; 

	}

	ret = deallocate(oldStocks, sizeof(Stock)*oldNumEntries);
	if(ret !=0)
		_terminate(DEALLOCATE_ERROR);

	return &portfolio->stocks[oldNumEntries];
}

void addStockToPortfolio(Stock stock, Portfolio* portfolio)
{

	Stock* newStock;
	newStock = getNextFreeEntry(portfolio);
	newStock->symbol = stock.symbol;
	newStock->purchasedPrice = stock.purchasedPrice;
	newStock->currentPrice = stock.currentPrice;
}

void buyStock(const char symbol, unsigned int price, Portfolio* portfolio)
{
	if(portfolio->cashBalance >= price) {

		Stock stock;
		stock.symbol = symbol;
		stock.purchasedPrice = price;
		stock.currentPrice = price;

		addStockToPortfolio(stock, portfolio);
		portfolio->cashBalance -= price;

	}

}

Stock* findMostExpensiveStock(char symbol, Portfolio* portfolio) {

	Stock* mostExpensiveStock=NULL;
	int entry;
	int price=0;
	// Checks to make sure portfolio has been initiated.
	for(entry = 0; portfolio->numEntries > 0 && portfolio->stocks[entry].purchasedPrice != 0 && entry<portfolio->numEntries; entry++) {				
		Stock* stock;
		stock = &portfolio->stocks[entry];
		if(stock->symbol == symbol) {
			if(stock->purchasedPrice > price) {
				mostExpensiveStock = stock;
				price = stock->purchasedPrice;
			}
		}
	}

	return mostExpensiveStock;
}


void sellStock(char symbol, unsigned int price, Portfolio* portfolio)
{
	
	if(portfolio->numEntries > 0) {
		Stock *stock;

		stock = findMostExpensiveStock(symbol, portfolio);

		if(stock != NULL) {
			portfolio->cashBalance += price;

			// remove stock form portfolio
			stock->symbol = 0;
			stock->purchasedPrice = 0;
			stock->currentPrice = 0;
		}
	}

}

void tradeStocks(Record record, Dataset dataset, Portfolio* portfolio)
{
	float priceRelative;

	priceRelative = (float)record.x / record.y;

	if(priceRelative > dataset.mean + dataset.stdDev) {
		sellStock(X_STR, record.x, portfolio);
		buyStock(Y_STR, record.y, portfolio);
	}

	if(priceRelative < dataset.mean - dataset.stdDev) {
		sellStock(Y_STR, record.y, portfolio);
		buyStock(X_STR, record.x, portfolio);
	}



}

void sendGoalNotification() {

	int ret;

	ret = transmit_all(STDOUT, GOAL_STR, strlen(GOAL_STR));
	if(ret != 0)
		_terminate(TRANSMIT_ERROR);

}

void sellAllStock(Record record, Portfolio* portfolio) {

	int entry;
#ifdef PATCHED
	// Checks to make sure portfolio has been initiated.
	for(entry = 0; portfolio->numEntries > 0 && portfolio->stocks[entry].purchasedPrice != 0 && entry<portfolio->numEntries; entry++) {
#else
	// If a Balance record has not been set, then portfolio isn't initailized and the for loop condition will cause a Segementation fault.
	for(entry = 0; portfolio->stocks[entry].purchasedPrice != 0; entry++) {
#endif			
		sellStock(portfolio->stocks[entry].symbol, portfolio->stocks[entry].currentPrice, portfolio);
	}
}

void updateStockValues(Record record, Portfolio* portfolio) {
	
	int entry;
#ifdef PATCHED
	// Checks to make sure portfolio has been initiated.
	for(entry = 0; portfolio->numEntries > 0 && portfolio->stocks[entry].purchasedPrice != 0 && entry<portfolio->numEntries; entry++) {
#else
	// If a Balance record has not been set, then portfolio isn't initailized and the for loop condition will cause a Segementation fault.
	for(entry = 0; portfolio->stocks[entry].purchasedPrice != 0; entry++) {
#endif		
		Stock* stock;
		stock = &portfolio->stocks[entry];

		portfolio->assetBalance -= stock->currentPrice;

		if(stock->symbol == X_STR) 
			stock->currentPrice = record.x;

		if(stock->symbol == Y_STR)
			stock->currentPrice = record.y;

		portfolio->assetBalance += stock->currentPrice;

	}
}

void initPortfolio(Portfolio* portfolio, unsigned int startingBalance)
{
	int ret;

	portfolio->cashBalance = startingBalance;
	portfolio->assetBalance = portfolio->cashBalance;
	portfolio->goal = portfolio->assetBalance*2;
	portfolio->numEntries = INIT_ENTRY_LIST;
	ret = allocate(sizeof(Stock)*portfolio->numEntries, 0, (void **) &portfolio->stocks);
	if(ret != 0)
		_terminate(ALLOCATE_ERROR);

}

int main(void) {
	Dataset dataset;
	Portfolio portfolio;
	Record record;
	int recordType;

	dataset.sampleSize = 0;

	while((recordType = nextRecord(&record)) != NO_MORE_RECORDS) {

		if(recordType == BALANCE_RECORD) {
			initPortfolio(&portfolio, record.y);
			continue;
		}

		if(dataset.sampleSize > LEARNING_MODE_SIZE) {

			updateStockValues(record, &portfolio);
			
			if(portfolio.assetBalance >= portfolio.goal) {

				sellAllStock(record, &portfolio);
				sendGoalNotification();
			}

			// check to see if out of cash
			if(portfolio.cashBalance == 0) {

				// If out of stock, quit
				if(portfolio.assetBalance == 0)
					break;

				// sell all stock to raise cash
				sellAllStock(record, &portfolio);
			}


			tradeStocks(record, dataset, &portfolio);

		}

		addRecordToDataset(&dataset, record);



	}

	return 0;

}
