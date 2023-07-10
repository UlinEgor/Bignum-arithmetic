struct thuge {
	#define ll long long
	#define re return
	#define all(x) x.begin(), x.end()
	#define fori(n) for(ll i = 0; i < n; i++)

	ll fast_pow(ll n, ll p) {
		if (p == 1)re n;
		if (p % 2)re n* fast_pow(n, p - 1);
		re fast_pow(n * n, p / 2);
	}

	vector<ll> v;
	ll foot;
	const int st = 9;
	bool neg = 0;

	void build_from_string(string s) {
		reverse(all(s));
		if (s.back() == '-') {
			neg = 1;
			s.pop_back();
		}
		reverse(all(s));

		v.clear();
		for (int i = 0; i < (s.size() + 8) / 9; i++) {
			ll n = 0;
			for (int j = max<int>(0, s.size() - (i + 1) * 9); j < s.size() - i * 9; j++)
				n = n * 10 + s[j] - '0';
			v.push_back(n);
		}
	}

	void equal(thuge& t) { v = t.v; neg = t.neg; }
	friend bool is_equal(thuge a, thuge b) { re(a.v == b.v && a.neg == b.neg); }

	friend bool is_larger(thuge a, thuge b) {
		if (a.v.size() != b.v.size())re a.v.size() > b.v.size();
		for (int i = a.v.size() - 1; i >= 0; --i) {
			if (a.v[i] == b.v[i])continue;
			re a.v[i] > b.v[i];
		}
		re false;
	}

	void clear_zero(vector<ll>& v) {
		while (v.size() > 1 && v.back() == 0)v.pop_back();
	}

	vector<ll> sum(vector<ll> a, vector<ll> b) {
		ll bn = 0;
		fori(max(a.size(), b.size())) {
			if (a.size() == i)a.push_back(0);

			ll q = (a[i] + (i < b.size() ? b[i] : 0) + bn) / foot;
			a[i] = (a[i] + (i < b.size() ? b[i] : 0) + bn) % foot;
			bn = q;
		}
		if (bn)a.push_back(bn);

		re a;
	}

	vector<ll> minus(vector<ll> a, vector<ll> b) {// a.size() >= b.size()
		ll bn = 0;
		fori(a.size()) {
			a[i] = (a[i] - (i < b.size() ? b[i] : 0) + bn);

			bn = 0;
			if (a[i] < 0) {
				a[i] += foot;
				bn = -1;
			}
			else if (a[i] >= foot) {
				bn = a[i] / foot;
				a[i] %= foot;
			}
		}

		clear_zero(a);
		re a;
	}

	vector<ll> multiply(vector<ll> a, ll b) {
		ll bn = 0;
		fori(a.size()) {
			ll q = (a[i] * b + bn) / foot;
			a[i] = (a[i] * b + bn) % foot;
			bn = q;
		}
		if (bn)a.push_back(bn);

		re a;
	}

	template<class T>void build(T n) {
		if constexpr (is_same_v<T, string>) { build_from_string(n); }
		else if constexpr (is_same_v<T, thuge>) { equal(n); }
		else build_from_string(to_string(n));
	}

	thuge() { foot = fast_pow(10, st); v.push_back(0); }

	thuge& operator=(const string& other) {
		build_from_string(other);

		re* this;
	}

	thuge& operator=(const thuge& other) {
		this->v = other.v;
		this->neg = other.neg;

		re* this;
	}

	thuge& operator=(const int& other) {
		build(other);
		re* this;
	}

	thuge& operator=(const ll& other) {
		build(other);
		re* this;
	}

	friend bool operator==(const thuge& a, const thuge& other) { re a.v == other.v && a.neg == other.neg; }
	template<class T> friend bool operator==(const thuge& a, const T& other) { thuge t; t = other; re t == a; }
	friend bool operator!=(const thuge& a, const thuge& other) { re !(a.v == other.v && a.neg == other.neg); }

	friend bool operator>(const thuge& a, const thuge& other) {
		if (a.neg != other.neg)re !a.neg;
		if (is_equal(a, other))re 0;

		if (!a.neg) re is_larger(a, other);
		re !is_larger(a, other);
	}

	friend bool operator<(const thuge& a, const thuge& other) {
		if (a.neg != other.neg)re a.neg;
		if (is_equal(a, other))re 0;


		if (!a.neg) re !is_larger(a, other);
		re is_larger(a, other);
	}

	friend bool operator>=(const thuge& a, const thuge& other) {
		if (a.neg != other.neg)re !a.neg;
		if (is_equal(a, other))re 1;

		if (!a.neg) re is_larger(a, other);
		re !is_larger(a, other);
	}

	friend bool operator<=(const thuge& a, const thuge& other) {
		if (a.neg != other.neg)re a.neg;
		if (is_equal(a, other))re 1;

		if (!a.neg) re !is_larger(a, other);
		re is_larger(a, other);
	}

	thuge operator+(const thuge& other) {
		thuge a, b = other;
		a.v = this->v;
		a.neg = this->neg;

		if (a.neg == b.neg)a.v = sum(a.v, b.v);
		else {
			if (a.neg)swap(a, b);

			if (is_larger(a, b)) {
				a.v = minus(a.v, b.v);
			}
			else {
				a.v = minus(b.v, a.v);
				a.neg = 1;
			}
		}

		re a;
	}

	thuge operator-(const thuge& other) {
		thuge a, b = other;
		a.v = this->v;
		a.neg = this->neg;
		b.neg = !b.neg;

		re a + b;
	}

	thuge& operator+=(const thuge& other) {
		thuge a, b = other;
		a.v = this->v;
		a.neg = this->neg;

		thuge c = a + b;
		v = c.v;
		neg = c.neg;

		re* this;
	}

	thuge& operator-=(const thuge& other) {
		thuge a, b = other;
		a.v = this->v;
		a.neg = this->neg;

		thuge c = a - b;
		v = c.v;
		neg = c.neg;

		re* this;
	}

	thuge operator*(const ll& other) {
		thuge a;
		a.v = this->v;
		a.neg = this->neg;

		if (other < 0) {
			a.neg = !a.neg;
		}
		ll q = abs((long long)other);

		a.v = multiply(a.v, q);
		re a;
	}

	thuge operator*(const thuge& other) {
		thuge a, b = other;
		a.v = this->v;
		a.neg = this->neg;

		if (a.neg == b.neg) {
			a.neg = 0;
			b.neg = 0;
		}

		if (a.neg)swap(a, b);

		thuge qa = a, ans;
		fori(b.v.size()) {
			ans += qa * b.v[i];
			qa = qa * foot;
		}

		if (b.neg)ans.neg = 1;

		re ans;
	}

	thuge& operator*=(const ll& other) {
		thuge a;
		a.v = this->v;
		a.neg = this->neg;

		a = a * other;

		this->v = a.v;
		this->neg = a.neg;

		re* this;
	}

	thuge& operator*=(const thuge& other) {
		thuge a, b = other;
		a.v = this->v;
		a.neg = this->neg;

		a = a * other;

		this->v = a.v;
		this->neg = a.neg;

		re* this;
	}

	template<class T> thuge operator%(const T& other) {
		thuge ans;
		ll bn = 0;
		for (int i = this->v.size() - 1; i >= 0; --i) {
			bn = (bn * foot + this->v[i]) % other;
		}

		if (this->neg)ans.v = { (other - bn) % other };
		else ans.v = { bn };

		re ans;
	}

	template<class T> thuge operator/(const T& other) {
		thuge ans;
		ans.neg = this->neg;
		ans.v.resize(this->v.size());

		if (other < 0)ans.neg = !ans.neg;
		ll q = abs(other);

		ll bn = 0;
		for (int i = this->v.size() - 1; i >= 0; --i) {
			bn = bn * foot + this->v[i];
			ans.v[i] = bn / q;
			bn %= q;
		}

		clear_zero(ans.v);
		re ans;
	}

	template<class T> thuge& operator/=(const T& other) {
		*this = *this / other;

		re* this;
	}

	template<class T>thuge& operator%=(const T& other) {
		*this = *this % other;

		re* this;
	}
};

istream& operator>>(istream& s, thuge& a) {
	string q; s >> q;
	a.build(q);
	re s;
}

ostream& operator<<(ostream& s, const thuge& a) {
	string q = "";
	bool neg = a.neg;
	if (a.v.size() == 1 && a.v[0] == 0)neg = 0;
	q = to_string(a.v.back());
	for (int i = a.v.size() - 2; i >= 0; --i) {
		string g = to_string(a.v[i]);
		while (g.size() < a.st)g = "0" + g;
		q += g;
	}

	re s << (neg ? "-" : "") + q;
}
