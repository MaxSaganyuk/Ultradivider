#include <iostream>
#include <ctime>
#include <string>
#include <vector>

using ll = long long;

std::string big_num_to_base(ll big_num, int base, std::string alph, bool nonsymb) {
	std::string res = "";
	int proto_res = 0;

	ll a = 1;
	int i;

	for (i = 0; a <= big_num; ++i) a *= base;
	--i;
	a /= base;

	/*
	std::cout << big_num << std::endl;
	std::cout << a << std::endl;
	std::cout << i << std::endl;
	*/

	while (i > -1) {
		if (big_num - a >= 0) {
			++proto_res;
			big_num -= a;
		}
		else {
			if (nonsymb) res += std::to_string(proto_res) + " ";
			else res += alph[proto_res];

			a /= base;
			proto_res = 0;

			--i;
		}
	}
	//std::cout << res << std::endl << std::endl;

	return res;
}

void divide() {
	
}

extern "C"{

__declspec(dllexport) const char* Udiv(ll n, ll k, int base, bool nonsymb) {
	if (k == 0) {
		return "Undefined";
	}

	if (base > 60) nonsymb = true;

	std::string alph = "0123456789ABCDEFGHJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz";

	std::string full_res = "";
	std::string res = "";
	std::vector<ll> res_ll;

	int mem_n = n;

	int counter = 0;
	ll proto_ost_1 = 0;
	ll proto_ost_2 = 0;
	std::vector<ll> ost_1;
	std::vector<ll> ost_2;
	bool stop_this = false;
	bool stop_this_special = false;
	bool stop_inside = false;

	int i = 0;
	int j = 0;
	ll big_num = 0;
	std::string big_num_str;

	while (n >= k) {
		n -= k;
		++big_num;
	}
	if (big_num > 0 && base != 10) big_num_str = big_num_to_base(big_num, base, alph, nonsymb);
	else big_num_str = std::to_string(big_num);

	if (n != 0) {
		while (!stop_this) {
			if (n < k) {
				if (counter > 0) {
					for (j = 0; j < ost_1.size(); ++j) {
						if (n == ost_1[j] && n * base == ost_2[j]) {
							stop_this = true;
							break;
						}
					}
					if (!stop_this) {
						if (!nonsymb) res += "0";
						else res_ll.push_back(0);

						ost_1.push_back(n);
						ost_2.push_back(n * base);
					}
				}
				n *= base;
				++counter;
			}
			else {
				counter = 0;
				stop_inside = false;
				i = n / k;

				if (n % k == 0) {
					if (!nonsymb) res += alph[i];
					else res_ll.push_back(i);

					stop_this = true;
					stop_this_special = true;
					stop_inside = true;
				}
				else{
					proto_ost_1 = n;

					n -= (k * i);
					proto_ost_2 = n;

					for (j = 0; j < ost_1.size(); ++j) {
						if (proto_ost_1 == ost_1[j] and proto_ost_2 == ost_2[j]) {
							stop_this = true;
							break;
						}
					}
					if (!stop_this) {
						if (!nonsymb) res += alph[i];
						else res_ll.push_back(i);

						ost_1.push_back(proto_ost_1);
						ost_2.push_back(proto_ost_2);
					}
					stop_inside = true;
				}
			}
		}
	}
	else {
		if (!nonsymb) res += "0";
		else res_ll.push_back(0);
		j = 0;
	}

	if (stop_this_special) {
		if (!nonsymb) res += "0";
		else res_ll.push_back(0);
		j = (!nonsymb ? res.length() : res_ll.size()) - 1;
	}

	full_res += big_num_str + ".";
	if (nonsymb) full_res += " ";

	int count;
	int per_amount = 0;
	for (count = 0; count < (!nonsymb ? res.length() : res_ll.size()); ++count) {
		if (count == j) {
			per_amount = count;
			full_res += "(";
		}
		if (!nonsymb) full_res += res[count];
		else full_res += std::to_string(res_ll[count]) + " ";
	}
	full_res += ")";

	per_amount = count - per_amount;

	return full_res.c_str();
}

}