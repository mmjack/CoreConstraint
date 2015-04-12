#include "core.h"

using namespace VM;

Core::Core() {
	_registers = new uint32_t[NUM_REGISTERS];
	setupJumpTable();
}

Core::~Core() {
	delete[] _registers;
}

void Core::setupJumpTable() {
	_jumpTable = new std::function<void(Core*)>[255];
	_jumpTable[NoOp] = &Core::noOp;
	_jumpTable[LoadImmediate] = &Core::loadImmediate;
	_jumpTable[JumpImmediate] = &Core::jumpImmediate;
	_jumpTable[AddRegister] = &Core::addRegister;
	_jumpTable[SubtractRegister] = &Core::subtractRegister;
	_jumpTable[MultiplyRegister] = &Core::multiplyRegister;
	_jumpTable[DivideRegister] = &Core::divideRegister;
}

void Core::setData(uint8_t* data, unsigned int dataSize) {
	_data = data;
	_maxData = dataSize;
}

void Core::run() {
	_registers[ProgramCounter] = 0;
	while (_registers[ProgramCounter] < _maxData) {
		_jumpTable[_data[_registers[ProgramCounter]]](this);
	}
}