#pragma once
// Operand.h

#ifndef OPERAND_H
#define OPERAND_H

class Operand {
public:
	virtual ~Operand() {};
};

class Number: public Operand {
public:
	double value;
	Number(double value) :value(value) {};
	virtual ~Number() {};

};

class Operator : public Operand {

};

class Add : public Operator {

};

class Subtract : public Operator {

};

class Multiply : public Operator {

};

class Divide : public Operator {

};

class Square : public Operator {

};


#endif

// end of Operand.h
