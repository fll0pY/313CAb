#define MOD 100003
#define BASE 1867

// Hash pentru bonuri

template <typename Tkey, typename Tvalue>
struct Pair {
	Tkey first;
	Tvalue second;
};

template <typename Tkey, typename Tvalue>
class HashBon {
private:
	ResizableArray < Pair < Tkey, ResizableArray < Tvalue > > > *H;
	int Hmax;
public:
	HashBon() {

	}

	HashBon(int Hmax) {
		this->Hmax = Hmax;
		H = new ResizableArray < Pair < Tkey, ResizableArray < Tvalue > > >[Hmax];
	}

	~HashBon() {
		delete[] H;
	}


	int logPow(int base, int exponent) {
		int res = 1;
		while (exponent > 0) {
			if (exponent & 1) {
				res = (1LL * res * base) % MOD;
			}

			base = (1LL * base * base) % MOD;
			exponent >>= 1;
		}
		return res;
	}

	int hashFunction(Tkey key) {
		int sum = 0, sz = key.size();
		for (int i = 0; i < sz; ++i) {
			sum = (sum + (logPow(BASE, sz - i - 1) * (int)(key[i])) % MOD) % MOD;
		}
		return sum;
	}


	void insert(Tkey key, Tvalue value) {
		Pair < Tkey, ResizableArray < Tvalue > > data;

		int hashKey = hashFunction(key);
		int ok = 0;

		if (H[hashKey].size() > 0) {
			int sz = H[hashKey].size();
			for (int i = 0; i < sz && !ok; ++i) {
				if (H[hashKey][i].first == key) {
					H[hashKey][i].second.push_back(value);
					return;
				}
			}
		}

		data.first = key;
		data.second.push_back(value);
		H[hashKey].push_back(data);
	}


	int getValue(Tkey key) {
		int hashKey = hashFunction(key);
		int sz = H[hashKey].size();

		for (int i = 0; i < sz; ++i) {
			if (H[hashKey][i].first == key) {
				return H[hashKey][i].second;
			}
		}

		return ResizableArray < Tvalue >();
	}

	ResizableArray < Pair < Tkey, ResizableArray < Tvalue > > >& operator[](int position) {
		if (position >= Hmax) {
			cerr << "Pozitie invalida!\n";
			return H[0];
		}

		return H[position];
	}

};


// Hash generic

template <typename Tkey, typename Tvalue>
class HashGen {
private:
	ResizableArray < Pair < Tkey, Tvalue > > *H;
	int Hmax;
public:
	// Constructor
	HashGen(int Hmax) {
		this->Hmax = Hmax;
		H = new ResizableArray < Pair < Tkey, Tvalue > >[Hmax];
	}

	// Destructor
	~HashGen() {
		delete[] H;
	}


	int logPow(int base, int exponent) {
		int res = 1;
		while (exponent > 0) {
			if (exponent & 1) {
				res = (1LL * res * base) % MOD;
			}

			base = (1LL * base * base) % MOD;
			exponent >>= 1;
		}
		return res;
	}

	int hashFunction(Tkey key) {
		int sum = 0, sz = key.size();
		for (int i = 0; i < sz; ++i) {
			sum = (sum + (logPow(BASE, sz - i - 1) * (int)(key[i])) % MOD) % MOD;
		}
		return sum;
	}

	void insert(Tkey key, Tvalue value) {
		Pair < Tkey, Tvalue > data;
		int hashKey = hashFunction(key);

		data.first = key;
		data.second = value;
		H[hashKey].push_back(data);
	}

	Tvalue getValue(Tkey key) {
		int hashKey = hashFunction(key);
		int sz = H[hashKey].size();

		for (int i = 0; i < sz; ++i) {
			if (H[hashKey][i].first == key) {
				return H[hashKey][i].second;
			}
		}

		return Tvalue();
	}

	ResizableArray<Tvalue> operator[](int position) {
		if (position >= Hmax) {
			cerr << "Pozitie invalida!\n";
			return H[0];
		}

		return H[position];
	}
};
