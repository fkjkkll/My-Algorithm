#include <iostream>
#include <stdlib.h>
using namespace std;

#define HALF_WORD   uint16_t
#define WORD        uint32_t

void showBits(void* d, int len) {
	int bytes = len / 8;
	unsigned char* p = (unsigned char*)d;
	for (int i = 0; i < bytes; i++) {
		unsigned char tmp = 0x80;
		for (int j = 0; j < 8; j++) {
			if (tmp & *p)
				printf("1");
			else
				printf("0");
			tmp >>= 1;
		}
		printf(" ");
		++p;
	}
	printf("\n");
}

int bitcopy(void* to, unsigned int tOfs, const void* from, unsigned int fOfs, int bCnt) {
	int BitsOfHalfWord = sizeof(HALF_WORD) * 8;	// 2 * 8 = 16
	// align data and offset to HALF_WORD
	to = (void*)((intptr_t)to + (tOfs / BitsOfHalfWord) * sizeof(HALF_WORD));
	from = (void*)((intptr_t)from + (fOfs / BitsOfHalfWord) * sizeof(HALF_WORD));
	fOfs %= BitsOfHalfWord;
	tOfs %= BitsOfHalfWord;

	int NbrOfCopiedBits = 0;
	WORD rMask, wMask;
	WORD temp, * _to = (WORD*)to, * _from = (WORD*)from;
	while (bCnt > 0) {
		// update counter
		int BitsToCopy = (bCnt < BitsOfHalfWord) ? bCnt : BitsOfHalfWord;
		bCnt -= BitsToCopy;
		NbrOfCopiedBits += BitsToCopy;
		// mask reading from '_from' and mask writing to '_to'
		rMask = (((WORD)-1) << fOfs) ^ (((WORD)-1) << (fOfs + BitsToCopy));
		wMask = (((WORD)-1) << tOfs) ^ (((WORD)-1) << (tOfs + BitsToCopy));
		temp = (*_from & rMask) >> fOfs << tOfs;
		*_to &= ~wMask;
		*_to |= temp;
		// increase data pointer if copy is not completed
		if (BitsToCopy == BitsOfHalfWord) {
			_to = (WORD*)((intptr_t)_to + sizeof(HALF_WORD));
			_from = (WORD*)((intptr_t)_from + sizeof(HALF_WORD));
		}
	}
	return NbrOfCopiedBits;
}

WORD shiftLeft(WORD w, int len) {
	unsigned char* s = (unsigned char*)&w;
	while (len--) {
		*(s) <<= 1;
		for (int i = 1; i < 4; i++) {
			if (*(s + i) == 0)
				continue;
			if (*(s + i) & 0x80)
				*(s + i - 1) |= 1;
			*(s + i) <<= 1;
		}
	}
	return w;
}

WORD shiftRight(WORD w, int len) {
	unsigned char* s = (unsigned char*)&w;
	while (len--) {
		*(s+3) >>= 1;
		for (int i = 2; i >= 0; i--) {
			if (*(s + i) == 0)
				continue;
			if (*(s + i) & 1)
				*(s + i + 1) |= 0x80;
			*(s + i) >>= 1;
		}
	}
	return w;
}

int bitcpy(void* to, unsigned int tOfs, const void* from, unsigned int fOfs, int bCnt) {
	int BitsOfHalfWord = sizeof(HALF_WORD) * 8;
	// 将数据和偏置对其“半字”
	// 指针视为intptr_t，加1则前进一个Byte，且更安全
	to = (void*)((intptr_t)to + (tOfs / BitsOfHalfWord) * sizeof(HALF_WORD));
	from = (void*)((intptr_t)from + (fOfs / BitsOfHalfWord) * sizeof(HALF_WORD));
	fOfs %= BitsOfHalfWord;
	tOfs %= BitsOfHalfWord;
	int NbrOfCopiedBits = 0;
	WORD rMask, wMask;
	WORD temp;
	WORD *_to = (WORD*)to;
	WORD *_from = (WORD*)from;
	while (bCnt > 0) {
		// 更新
		int BitsToCopy = (bCnt < BitsOfHalfWord) ? bCnt : BitsOfHalfWord;
		bCnt -= BitsToCopy;
		NbrOfCopiedBits += BitsToCopy;
		// 源与目标的遮罩
		rMask = shiftRight((WORD)-1, fOfs) ^ shiftRight((WORD)-1, fOfs + BitsToCopy);
		wMask = shiftRight((WORD)-1, tOfs) ^ shiftRight((WORD)-1, tOfs + BitsToCopy);
		temp = (*_from & rMask);
		temp = shiftLeft(temp, fOfs);
		temp = shiftRight(temp, tOfs);
		*_to &= ~wMask;	// 先清理此部分
		*_to |= temp;	// 在“拷贝”进来
		// 拷贝未完成情况下，跟进指针
		if (BitsToCopy == BitsOfHalfWord) {
			_to = (WORD*)((intptr_t)_to + sizeof(HALF_WORD));
			_from = (WORD*)((intptr_t)_from + sizeof(HALF_WORD));
		}
	}
	return NbrOfCopiedBits;
}

int main() {
	int a = 0x87654321;
	int b = 0;
	int c = 0;
	showBits(&a, 32);
	bitcpy(&c, 4, &a, 0, 16);
	showBits(&c, 32);
	return 0;
}
