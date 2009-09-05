// $Id$
/** \file expression.h Implements an example calculator class group. */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <map>
#include <vector>
#include <ostream>
#include <stdexcept>
#include <cmath>

/** CalcNode is the abstract base class for calculation nodes. From it the
 * different nullary, unary and binary nodes are derived. */
class CalcNode
{
public:
    /// required for virtual functions. in the derived classes the operands are
    /// deleted.
    virtual ~CalcNode()
    {
    }

    /// evaluate the complete calculation tree and return the floating point
    /// result value
    virtual double	evaluate() const = 0;

    /// output the calculation tree to the given stream. tries to format the
    /// output to make tree levels visible.
    virtual void	print(std::ostream &os, unsigned int depth=0) const = 0;

    /// helper function for print() which makes the indention string
    static inline std::string indent(unsigned int d)
    {
	return std::string(d * 2, ' ');
    }
};

/** Calculation node always returning a constant value. */
class CNConstant : public CalcNode
{
    /// the constant value returned
    double	value;
    
public:
    /// construct a constant calculation node from a value
    explicit CNConstant(double _value)
	: CalcNode(), value(_value)
    {
    }

    virtual double evaluate() const
    {
	return value;
    }

    virtual void print(std::ostream &os, unsigned int depth) const
    {
	os << indent(depth) << value << std::endl;
    }
};

/** Calculation node negating the value of the operand subtree. */
class CNNegate : public CalcNode
{
    /// calculation subtree
    CalcNode* 	node;

public:
    explicit CNNegate(CalcNode* _node)
	: CalcNode(), node(_node)
    {
    }

    virtual ~CNNegate()
    {
	delete node;
    }

    virtual double evaluate() const
    {
	return - node->evaluate();
    }

    virtual void print(std::ostream &os, unsigned int depth) const
    {
	os << indent(depth) << "- negate" << std::endl;
	node->print(os, depth+1);
    }
};

/** Calculation node adding two operand nodes. */
class CNAdd : public CalcNode
{
    /// left calculation operand
    CalcNode* 	left;

    /// right calculation operand
    CalcNode* 	right;
    
public:
    explicit CNAdd(CalcNode* _left, CalcNode* _right)
	: CalcNode(), left(_left), right(_right)
    {
    }

    virtual ~CNAdd()
    {
	delete left;
	delete right;
    }

    virtual double evaluate() const
    {
	return left->evaluate() + right->evaluate();
    }

    virtual void print(std::ostream &os, unsigned int depth) const
    {
	os << indent(depth) << "+ add" << std::endl;
	left->print(os, depth+1);
	right->print(os, depth+1);
    }
};

/** Calculation node subtracting two operand nodes. */
class CNSubtract : public CalcNode
{
    /// left calculation operand
    CalcNode* 	left;

    /// right calculation operand
    CalcNode* 	right;
    
public:
    explicit CNSubtract(CalcNode* _left, CalcNode* _right)
	: CalcNode(), left(_left), right(_right)
    {
    }

    virtual ~CNSubtract()
    {
	delete left;
	delete right;
    }

    virtual double evaluate() const
    {
	return left->evaluate() - right->evaluate();
    }

    virtual void print(std::ostream &os, unsigned int depth) const
    {
	os << indent(depth) << "- subtract" << std::endl;
	left->print(os, depth+1);
	right->print(os, depth+1);
    }
};

/** Calculation node multiplying two operand nodes. */
class CNMultiply : public CalcNode
{
    /// left calculation operand
    CalcNode* 	left;

    /// right calculation operand
    CalcNode* 	right;
    
public:
    explicit CNMultiply(CalcNode* _left, CalcNode* _right)
	: CalcNode(), left(_left), right(_right)
    {
    }

    virtual ~CNMultiply()
    {
	delete left;
	delete right;
    }

    virtual double evaluate() const
    {
	return left->evaluate() * right->evaluate();
    }

    virtual void print(std::ostream &os, unsigned int depth) const
    {
	os << indent(depth) << "* multiply" << std::endl;
	left->print(os, depth+1);
	right->print(os, depth+1);
    }
};

/** Calculation node dividing two operand nodes. */
class CNDivide : public CalcNode
{
    /// left calculation operand
    CalcNode* 	left;

    /// right calculation operand
    CalcNode* 	right;
    
public:
    explicit CNDivide(CalcNode* _left, CalcNode* _right)
	: CalcNode(), left(_left), right(_right)
    {
    }

    virtual ~CNDivide()
    {
	delete left;
	delete right;
    }

    virtual double evaluate() const
    {
	return left->evaluate() / right->evaluate();
    }

    virtual void print(std::ostream &os, unsigned int depth) const
    {
	os << indent(depth) << "/ divide" << std::endl;
	left->print(os, depth+1);
	right->print(os, depth+1);
    }
};

/** Calculation node calculating the remainder of an integer division of two
 * operand nodes. */
class CNModulo : public CalcNode
{
    /// left calculation operand
    CalcNode* 	left;

    /// right calculation operand
    CalcNode* 	right;
    
public:
    explicit CNModulo(CalcNode* _left, CalcNode* _right)
	: CalcNode(), left(_left), right(_right)
    {
    }

    virtual ~CNModulo()
    {
	delete left;
	delete right;
    }

    virtual double evaluate() const
    {
	return std::fmod(left->evaluate(), right->evaluate());
    }

    virtual void print(std::ostream &os, unsigned int depth) const
    {
	os << indent(depth) << "% modulo" << std::endl;
	left->print(os, depth+1);
	right->print(os, depth+1);
    }
};

/** Calculation node raising one operand to the power of the second. */
class CNPower : public CalcNode
{
    /// left calculation operand
    CalcNode* 	left;

    /// right calculation operand
    CalcNode* 	right;
    
public:
    explicit CNPower(CalcNode* _left, CalcNode* _right)
	: CalcNode(), left(_left), right(_right)
    {
    }

    virtual ~CNPower()
    {
	delete left;
	delete right;
    }

    virtual double evaluate() const
    {
	return std::pow(left->evaluate(), right->evaluate());
    }

    virtual void print(std::ostream &os, unsigned int depth) const
    {
	os << indent(depth) << "^ power" << std::endl;
	left->print(os, depth+1);
	right->print(os, depth+1);
    }
};

/** Calculator context used to save the parsed expressions. This context is
 * passed along to the example::Driver class and fill during parsing via bison
 * actions. */
class CalcContext
{
public:

    /// type of the variable storage
    typedef std::map<std::string, double> variablemap_type;

    /// variable storage. maps variable string to doubles
    variablemap_type		variables;

    /// array of unassigned expressions found by the parser. these are then
    /// outputted to the user.
    std::vector<CalcNode*>	expressions;

    /// free the saved expression trees
    ~CalcContext()
    {
	clearExpressions();
    }

    /// free all saved expression trees
    void	clearExpressions()
    {
	for(unsigned int i = 0; i < expressions.size(); ++i)
	{
	    delete expressions[i];
	}
	expressions.clear();
    }

    /// check if the given variable name exists in the storage
    bool	existsVariable(const std::string &varname) const
    {
	return variables.find(varname) != variables.end();
    }
    
    /// return the given variable from the storage. throws an exception if it
    /// does not exist.
    double	getVariable(const std::string &varname) const
    {
	variablemap_type::const_iterator vi = variables.find(varname);
	if (vi == variables.end())
	    throw(std::runtime_error("Unknown variable."));
	else
	    return vi->second;
    }
};

#endif // EXPRESSION_H
