#include "PT.h"
PT::PT() :time(99999), pagNum(-1), visit(0), state(false), blockNum(-1) {

};
PT::PT(int rn, int pn) :blockNum(rn), pagNum(pn), time(99999), state(false), visit(0) {

};
void PT::remove() {
	state = false;
	blockNum = -1;
	pN = NULL;
	time = -1;
	visit = -1;
};
void PT::insert(int rn) {
	blockNum = rn;
	state = true;

};