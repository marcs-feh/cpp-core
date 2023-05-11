#include "test/test.hpp"
#include "bitfield.hpp"

template<usize N>
void displayBitfield(const Bitfield<N>& bf){
	printf("[");
	ssize n = bf.cap() * 8;
	for(ssize i = n - 1; i >= 0; i -= 1){
		// printf("%td:", i);
		printf("%d", bf[i]);
		if((i != 0) && (i % 8 == 0)){ printf("|"); }
	}
	printf("]\n");
}

void test_bitfield(){
	Test T("Bitfield");
	{
		constexpr usize n = 11;
		Bitfield<n> b0;
		Bitfield<n> b1;
		Tp(b0.cap() == 2);
		Tp(b0.len() == n);
		b0 = {1, 0, 1, 1, 0};
		// displayBitfield(b0);
		Tp(b0.eq({0,0,0,0,0,0,/**/1,0,1,1,0}));
		Tp(!b0.eq({0,0,0,0,0,0,/**/0,0,1,1,0}));
		b1 = b0;
		Tp(b0 == b1);
	}
	{
		constexpr usize n = 6;
		Bitfield<n> b = {0,0,1,1,0,1};
		auto r = b & Bitfield<n>({1,1,1,1,1,1});
		Tp(b == r);
		r = b | Bitfield<n>({0,0,0,0,0,0});
		Tp(b == r);
		r = b ^ Bitfield<n>({1,1,1,1,1,1});
		Tp((~b) == r);
	}
	{
		Bitfield<6> bf = {1,1,1,1,1,1};
		Tp(bf.hasAll());
		bf.data[0] = 0xc0;
		Tp(!bf.hasAll());
	}
	{
		Bitfield<6> bf = {0,0,1,0,0,0};
		Tp(bf.hasAny());
		// displayBitfield(bf);
		bf.data[0] = 0xc0;
		// displayBitfield(bf);
		Tp(!bf.hasAny());
	}
	{
		Bitfield<12> bf = {1,1,1,1,1,1};
		Tp(!bf.hasAll());
		bf = {1,1,1,1,1,1,1,1,1,1,1,1};
		Tp(bf.hasAll());
	}
	{
		Bitfield<12> bf = {0};
		Tp(!bf.hasAny());
		bf = {0,0,0,0,1,0,0,0,0,0,0,0};
		Tp(bf.hasAny());
		bf = {0};
		bf.data[0] = 0xc0;
		Tp(!bf.hasAny());
	}
}
