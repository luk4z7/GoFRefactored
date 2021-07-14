#pragma once

#include <cstring>

namespace InterpreterPattern::Variant1
{
	class IContext {
	public:
		virtual bool Lookup(const char*) const = 0;
	};

	class BooleanExp {
	public:
		BooleanExp() {}
		virtual ~BooleanExp() {}
		virtual bool Evaluate(IContext&) = 0;
		virtual BooleanExp* Replace(const char*, BooleanExp&) = 0;
		virtual BooleanExp* Copy() const = 0;
	};

	class VariableExp : public BooleanExp {
	public:
		VariableExp(const char*);
		virtual ~VariableExp() {}
		virtual bool Evaluate(IContext&);
		virtual BooleanExp* Replace(const char*, BooleanExp&);
		virtual BooleanExp* Copy() const;
	private:
		char* _name;
	};

	VariableExp::VariableExp(const char* name) {
		//		_name = strdup(name);
	}

	bool VariableExp::Evaluate(IContext& aContext) {
		return aContext.Lookup(_name);
	}

	BooleanExp* VariableExp::Copy() const {
		return new VariableExp(_name);
	}

	BooleanExp* VariableExp::Replace(const char* name, BooleanExp& exp) {
		if (strcmp(name, _name) == 0) {
			return exp.Copy();
		}
		else {
			return new VariableExp(_name);
		}
	}

	class AndExp : public BooleanExp {
	public:
		AndExp(BooleanExp*, BooleanExp*);
		virtual ~AndExp() {}
		virtual bool Evaluate(IContext&);
		virtual BooleanExp* Replace(const char*, BooleanExp&);
		virtual BooleanExp* Copy() const;
	private:
		BooleanExp* _operand1;
		BooleanExp* _operand2;
	};

	AndExp::AndExp(BooleanExp* op1, BooleanExp* op2)
	{
		_operand1 = op1;
		_operand2 = op2;
	}

	bool AndExp::Evaluate(IContext& aContext) {
		return _operand1->Evaluate(aContext) && _operand2->Evaluate(aContext);
	}

	BooleanExp* AndExp::Copy() const
	{
		return new AndExp(_operand1->Copy(), _operand2->Copy());
	}

	BooleanExp* AndExp::Replace(const char* name, BooleanExp& exp) {
		return new AndExp(
			_operand1->Replace(name, exp),
			_operand2->Replace(name, exp)
		);
	}

	class Constant : public BooleanExp {
	public:
		Constant(bool) {}
		virtual bool Evaluate(IContext&) { return true; }
		virtual BooleanExp* Replace(const char*, BooleanExp&) { return 0; }
		virtual BooleanExp* Copy() const { return 0; }
	};

	class OrExp : public BooleanExp {
	public:
		OrExp(BooleanExp*, BooleanExp*) {}
		virtual bool Evaluate(IContext&) { return true; }
		virtual BooleanExp* Replace(const char*, BooleanExp&) { return 0; }
		virtual BooleanExp* Copy() const { return 0; }
	};

	class NotExp : public BooleanExp {
	public:
		NotExp(BooleanExp*) {}
		virtual bool Evaluate(IContext&) { return true; }
		virtual BooleanExp* Replace(const char*, BooleanExp&) { return 0; }
		virtual BooleanExp* Copy() const { return 0; }
	};

	class Context : public IContext {
	public:
		bool Lookup(const char*) const { return true; }
		void Assign(VariableExp*, bool) {}
	};
}
