#include <iostream>
#include <ctime>
#include <string>

std::string big_num_to_base(long long int big_num, int base, std::string alph, bool nonsymb){
	std::string res = "";
	int proto_res = 0;
	
	long long int a = 1;
	int i;

	for(i = 0; a <= big_num; ++i) a *= base;
	--i;
	a /= base;

	/*
	std::cout << big_num << std::endl;
	std::cout << a << std::endl;
	std::cout << i << std::endl;
	*/

	while(i > -1){
		if(big_num - a >= 0){
			++proto_res;
			big_num -= a;
		}
		else{
			if(nonsymb) res += std::to_string(proto_res) + " ";
			else res += alph[proto_res];

			a /= base;
			proto_res = 0;

			--i;
		}
	}
	//std::cout << res << std::endl << std::endl;

	return res;
}

int main(int argc, char* argv[]){
	if(argc < 3){ 
		std::cerr << "Invalid Params" << std::endl;
		return 1;
	}


	long long int n = atoi(argv[1]);
	long long int k = atoi(argv[2]);

	if(k == 0){
		std::cerr << "Can't Divide By 0" << std::endl;
		return 1;
	}

	clock_t time;
	time = clock();

	int base = 10;
	if(argc > 3) base = atoi(argv[3]);

	bool nonsymb = false;
	if(base > 60 || (argc > 4 && atoi(argv[4]) == 1)) nonsymb = true;

	std::string alph = "0123456789ABCDEFGHJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz";
	//std::cout << alph.length() << std::endl;

	std::string full_res = "";
	std::string res = "";
	long long int *res_lli;
	int res_len = 0;
	if(nonsymb) res_lli = new long long int[k];

	int mem_n = n;
	
	int counter = 0;
	long long int proto_ost_1 = 0;
	long long int proto_ost_2 = 0;
	long long int *ost_1 = new long long int[k];
	long long int *ost_2 = new long long int[k];
	int ost_1_len = 0;
	int ost_2_len = 0;
	bool stop_this = false;
	bool stop_this_special = false;
	bool stop_inside = false;

	int j = 0;
	long long int big_num = 0;
	std::string big_num_str;

	while(n >= k){
		n -= k;
		++big_num;
	}
	if(big_num > 0 && base != 10) big_num_str = big_num_to_base(big_num, base, alph, nonsymb);
	else big_num_str = std::to_string(big_num);

	if(n != 0){
		while(!stop_this){
			if(n < k){
				if(counter > 0){
					for(j = 0; j < ost_1_len; ++j){
						if(n == ost_1[j] && n * base == ost_2[j]){
							stop_this = true;
							break;
						}
					}
					if(!stop_this){
						if(!nonsymb) res += "0";
						else res_lli[res_len] = 0;
						++res_len;
						
						ost_1[ost_1_len++] = n;
						ost_2[ost_2_len++] = n * base;							
					}
				}
				n *= base;
				++counter;
			}
			else{
				counter = 0;
				stop_inside = false;
				for(int i = 1; !stop_inside; ++i){
					if(n - k * i == 0){
						if(!nonsymb) res += alph[i];
						else res_lli[res_len] = i;
						++res_len;
							
						stop_this = true;
						stop_this_special = true;
						stop_inside = true;
					}
					else if(n - k * i < 0){
						--i;
						proto_ost_1 = n;
					
						n -= (k * i);
						proto_ost_2 = n;

						for(j = 0; j < ost_1_len; ++j){
							if(proto_ost_1 == ost_1[j] and proto_ost_2 == ost_2[j]){
								stop_this = true;
								break;
							}
						}
						if(!stop_this){
							if(!nonsymb) res += alph[i];
							else res_lli[res_len] = i;
							++res_len;

							ost_1[ost_1_len++] = proto_ost_1;
							ost_2[ost_2_len++] = proto_ost_2;
						}
						stop_inside = true;
					}
				}
			}
		}
	}
	else{
		if(!nonsymb) res += "0";
		else res_lli[res_len] = 0;
		++res_len;
		j = 0;
	}

	if(stop_this_special){
		if(!nonsymb) res += "0";
		else res_lli[res_len] = 0;
		++res_len;
		j = res_len - 1;
	}

	time = clock() - time;

	//std::cout << "Done Calc" << std::endl;

	if(nonsymb) full_res += "Nonsymb/Nondigit representation is on\n\n";

	full_res += std::to_string(mem_n);
	full_res += " / ";
	full_res += std::to_string(k);
	full_res += " = ";
	full_res += big_num_str;
	full_res += ".";
	if(nonsymb) full_res += " "; 

	int count;
	int per_amount = 0;
	for(count = 0; count < res_len; ++count){
		if(count == j){
			per_amount = count;
			full_res += "(";
		}
		if(!nonsymb) full_res += res[count];
		else full_res += std::to_string(res_lli[count]) + " ";
	}
	full_res += ")";
	
	per_amount = count - per_amount;
	
	//std::cout << res << std::endl;
	std::cout << std::endl;
	std::cout << full_res << std::endl;
	std::cout << std::endl;
	std::cout << "Length of a period: " << per_amount << std::endl;
	std::cout << "It took " << (long double)time / CLOCKS_PER_SEC << " seconds" << std::endl;
	
}