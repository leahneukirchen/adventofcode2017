#include <iostream>
#include <string>
#include <algorithm>
#include <variant>
#include <vector>
#include <deque>
#include <memory>

using namespace std;

int part;
int p1 = 0;
int p2 = 0;

struct cpu;

struct insn {
	virtual void run(cpu &) = 0;
	virtual bool stalled(cpu &) { return false; }
};

struct cpu {
	int64_t reg[256];
	const vector<unique_ptr<insn>> &insns;
	vector<unique_ptr<insn>>::const_iterator ip;
	deque<uint64_t> &sndq, &rcvq;
	int id;

	cpu(const vector<unique_ptr<insn>> &insns,
	    deque<uint64_t> &sq, deque<uint64_t> &rq, int id=0) :
		reg{0}, insns{insns}, ip{cbegin(insns)}, sndq{sq}, rcvq{rq},
		id{id}
	{
		reg[(uint8_t)'p'] = id;
	}

	void step() { (*ip++)->run(*this); }
	bool done() { return ip == cend(insns); }
	bool stalled() { return (*ip)->stalled(*this); }
};

struct arg {
	virtual long operator()(cpu &) = 0;
};

struct const_arg : arg {
	long l;
	const_arg(long l) : l{l} {}
	long operator()(cpu &) { return l; }
};

struct reg_arg : arg {
	uint8_t r;
	reg_arg(uint8_t r) : r{r} {}
	long operator()(cpu &c) { return c.reg[r]; }
};

unique_ptr<arg>
parse(string s) {
	if (islower(s[0]))
		return make_unique<reg_arg>(uint8_t(s[0]));
	else
		return make_unique<const_arg>(stol(s));
}

struct binop : public insn {
public:
	uint8_t r;
	unique_ptr<arg> a;
	binop(string &s) : r(s[4]), a{parse(&s[6])} {};
};

struct opset : public binop { using binop::binop;
	void run(cpu &c) { c.reg[r] = (*a)(c); }
};
struct opadd : public binop { using binop::binop;
	void run(cpu &c) { c.reg[r] += (*a)(c); }
};
struct opmul : public binop { using binop::binop;
	void run(cpu &c) { c.reg[r] *= (*a)(c); }
};
struct opmod : public binop { using binop::binop;
	void run(cpu &c) { c.reg[r] %= (*a)(c); }
};
struct opjgz : public insn {
	unique_ptr<arg> a1, a2;
	opjgz(string &s) : a1{parse(&s[4])}, a2{parse(&s[6])} {}
	void run(cpu &c) { if ((*a1)(c) > 0) advance(c.ip, (*a2)(c) - 1); }
};
struct opsnd : public insn {
	unique_ptr<arg> a;
	opsnd(string &s) : a{parse(&s[4])} {}
	void run(cpu &c) { 
		if (part == 1) {
			p1 = (*a)(c);
		} else {
			if (c.id == 1)
				p2++;
			c.sndq.push_back((*a)(c));
		}
	}
};
struct oprcv : public insn {
	uint8_t r;
	oprcv(string &s) : r(s[4]) {}
	void run(cpu &c) {
		if (part == 2) {
			if (empty(c.rcvq)) {
				--c.ip;
			} else {
				c.reg[r] = c.rcvq.front();
				c.rcvq.pop_front();
			}
		}
	}
	bool stalled(cpu &c) { return part == 1 ? c.reg[r] > 0 : empty(c.rcvq); }
};

int
main() {
	string line;
	vector<unique_ptr<insn>> code;

	while (getline(cin, line)) {
		auto is_op = [&](string p){
			return equal(begin(p), end(p), begin(line));
		};

		insn* op;
		if      (is_op("set")) op = new opset{line};
		else if (is_op("add")) op = new opadd{line};
		else if (is_op("mul")) op = new opmul{line};
		else if (is_op("mod")) op = new opmod{line};
		else if (is_op("jgz")) op = new opjgz{line};
		else if (is_op("snd")) op = new opsnd{line};
		else if (is_op("rcv")) op = new oprcv{line};
		code.emplace_back(op);
	}

	part = 1;

	deque<uint64_t> _;
	for (cpu c{code, _, _}; !c.done() && !c.stalled(); c.step())
		;

	part = 2;

	deque<uint64_t> q01, q10;
	for (cpu c0{code, q01, q10, 0},
		 c1{code, q10, q01, 1};
	     !c0.done() && !c1.done() && !(c0.stalled() && c1.stalled());
	     c0.step(), c1.step())
		;

	cout << p1 << endl << p2 << endl;	// 3423 7493
}
