/*
 * nfc.h
 *
 *  Created on: Jun 6, 2025
 *      Author: chinabni
 */

#ifndef NFC_H_
#define NFC_H_

#include <stdio.h>
#include <stdint.h>

void nfc_init(void);
int receiveTag(void);
uint64_t getTag(void);
void waitTag(void);

#endif /* NFC_H_ */
