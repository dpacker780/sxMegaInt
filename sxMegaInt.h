#pragma once

#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <bitset>
#include <limits>
#include <array>

//********************************************************************************************/
// sxMegaInt: A std::bitset based big integer header-only class. 
//
//********************************************************************************************/

constexpr std::array<char, 10> SX_THE_ODDS{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };
constexpr unsigned int SX_MAX_LL_BITS = sizeof(long long) * CHAR_BIT;

template <std::size_t N>
class sxMegaInt {
    public:

        sxMegaInt() = default;
        sxMegaInt(const std::bitset<N>& bin_value)    { mValue = bin_value; }
        sxMegaInt(const std::string& dec_value)       { mValue = decstr2binary(dec_value); }
        sxMegaInt(const long long& dec_value)         { mValue = std::bitset<N>(dec_value); if(dec_value < 0) mValue |= ~mask_ll; }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// OPERATOR OVERLOADS

        sxMegaInt& operator=(const sxMegaInt& val)    { if(this == &val) return *this; mValue = val.mValue; return *this; }
        sxMegaInt& operator=(const std::string& val)  { mValue = decstr2binary(val); return *this; }
        sxMegaInt& operator=(const long long& val)    { mValue = neg_check(val); return *this; }

        sxMegaInt& operator+(const sxMegaInt& rhs)    { sxMegaInt nset = *this; nset.bin_add(nset.mValue, mValue, rhs.mValue); return nset; }
        sxMegaInt& operator+(const long long& rhs)    { sxMegaInt nset = *this; nset.bin_add(nset.mValue, mValue, neg_check(rhs)); return nset; }
        sxMegaInt& operator+(const std::string& rhs)  { sxMegaInt nset = *this; nset.bin_add(nset.mValue, mValue, decstr2binary(rhs));  return nset; }
        sxMegaInt& operator+=(const sxMegaInt& rhs)   { bin_add(mValue, mValue, rhs.mValue); return *this;  }
        sxMegaInt& operator+=(const long long& rhs)   { bin_add(mValue, mValue, neg_check(rhs)); return *this; }
        sxMegaInt& operator+=(const std::string& rhs) { bin_add(mValue, mValue, (decstr2binary(rhs))); return *this; }
        sxMegaInt& operator++() { bin_add(mValue, mValue, binary_one); return *this; }

        sxMegaInt& operator-(const sxMegaInt& rhs)    { sxMegaInt nset = *this; nset.bin_sub(nset.mValue, mValue, rhs.mValue); return nset; }
        sxMegaInt& operator-(const long long& rhs)    { sxMegaInt nset = *this; nset.bin_sub(nset.mValue, mValue, neg_check(rhs)); return nset; }
        sxMegaInt& operator-(const std::string& rhs)  { sxMegaInt nset = *this; nset.bin_sub(nset.mValue, mValue, decstr2binary(rhs)); return nset; }
        sxMegaInt& operator-=(const sxMegaInt& rhs)   { bin_sub(mValue, mValue, rhs.mValue); return *this;  }
        sxMegaInt& operator-=(const long long& rhs)   { bin_sub(mValue, mValue, std::bitset<N>(rhs)); return *this; }
        sxMegaInt& operator-=(const std::string& rhs) { bin_sub(mValue, mValue, decstr2binary(rhs)); return *this; }
        sxMegaInt& operator--() { bin_sub(mValue, mValue, binary_one); return *this; }

        sxMegaInt& operator*(const sxMegaInt& rhs)    { sxMegaInt nset = *this; nset.bin_mult(nset.mValue, mValue, rhs.mValue); return nset; }
        sxMegaInt& operator*(const long long& rhs)    { sxMegaInt nset = *this; nset.bin_mult(nset.mValue, mValue, neg_check(rhs)); return nset; }
        sxMegaInt& operator*(const std::string& rhs)  { sxMegaInt nset = *this; nset.bin_mult(nset.mValue, mValue, decstr2binary(rhs)); return nset; }
 
        sxMegaInt& operator*=(const sxMegaInt& rhs)   { bin_mult(mValue, mValue, rhs.mValue); return *this; }
        sxMegaInt& operator*=(const long long& rhs)   { bin_mult(mValue, mValue, neg_check(rhs)); return *this; }
        sxMegaInt& operator*=(const std::string& rhs) { bin_mult(mValue, mValue, decstr2binary(rhs)); return *this; }

        sxMegaInt& operator/(const sxMegaInt& rhs)    { sxMegaInt nset = *this; nset.bin_div(nset.mValue, mValue, rhs.mValue); return nset; }
        sxMegaInt& operator/(const long long& rhs)    { sxMegaInt nset = *this; nset.bin_div(nset.mValue, mValue, neg_check(rhs)); return nset; }
        sxMegaInt& operator/(const std::string& rhs)  { sxMegaInt nset = *this; nset.bin_div(nset.mValue, mValue, decstr2binary(rhs)); return nset; }
 
        sxMegaInt& operator/=(const sxMegaInt& rhs)   { bin_div(mValue, mValue, rhs.mValue); return *this; }
        sxMegaInt& operator/=(const long long& rhs)   { bin_div(mValue, mValue, neg_check(rhs)); return *this; }
        sxMegaInt& operator/=(const std::string& rhs) { bin_div(mValue, mValue, decstr2binary(rhs)); return *this; }

        bool operator==(const sxMegaInt& rhs)         { return binary_compare(mValue, rhs.mValue) == 0; }
        bool operator==(const long long& rhs)         { return binary_compare(mValue, neg_check(rhs)) == 0;  }
        bool operator==(const std::string& rhs)       { return binary_compare(mValue, decstr2binary(rhs)); }

        bool operator>(const sxMegaInt& rhs)          { return binary_compare(mValue, rhs.mValue) == 1; }
        bool operator>(const long long& rhs)          { return binary_compare(mValue, neg_check(rhs)) == 1;  }
        bool operator>(const std::string& rhs)        { return binary_compare(mValue, decstr2binary(rhs)) == 1; }

        bool operator>=(const sxMegaInt& rhs)         { return binary_compare(mValue, rhs.mValue) >= 0; }
        bool operator>=(const long long& rhs)         { return binary_compare(mValue, neg_check(rhs)) >= 0;  }
        bool operator>=(const std::string& rhs)       { return binary_compare(mValue, decstr2binary(rhs)) >= 0; }

        bool operator<(const sxMegaInt& rhs)          { return binary_compare(mValue, rhs.mValue) == -1; }
        bool operator<(const long long& rhs)          { return binary_compare(mValue, neg_check(rhs)) == -1;  }
        bool operator<(const std::string& rhs)        { return binary_compare(mValue, decstr2binary(rhs)) == -1; }

        bool operator<=(const sxMegaInt& rhs)         { return binary_compare(mValue, rhs.mValue) <= 0; }
        bool operator<=(const long long& rhs)         { return binary_compare(mValue, neg_check(rhs)) <= 0;  }
        bool operator<=(const std::string& rhs)       { return binary_compare(mValue, decstr2binary(rhs)) <= 0; }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// UTILITY

        sxMegaInt power(unsigned long long exp) {
            if(exp == 0) return sxMegaInt(binary_one);
            if(exp == 1) return *this;
            exp--;

            sxMegaInt nval = *this;
            while(exp--) { nval *= mValue; }
            return nval;
        }

        bool isNegative() { return is_negative(mValue); }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// NUMERIC CONVERSION -> STRING

        std::string to_binstring()  { return mValue.to_string(); }
        std::string to_decstring() { return to_decimal(mValue); }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// NUMERIC CONVERSION -> LONG LONG (Within the numeric limits) otherwise throws fatal.

        long long to_llong() { 
            try {
                std::bitset<N> tmp_value = mValue;
                if(isNegative()) tmp_value = mValue & mask_ll;
                unsigned long long ulongval = tmp_value.to_ullong();
                return *((long*)((void*)&ulongval));
            } catch(...) {
                std::cout << "Numeric overflow: long long - this value > " + std::to_string(SX_MAX_LL_BITS) + " bits in size." << std::endl;
                throw;
            }
        }

    protected:

        static inline const std::bitset<N> mask_ll = std::bitset<N>(std::string((N <= SX_MAX_LL_BITS ? N : SX_MAX_LL_BITS), '1'));
        static inline const std::bitset<N> binary_one = std::bitset<N>(1);
        static inline const std::bitset<N> binary_zero = std::bitset<N>(0);

        std::bitset<N> neg_check(const long long& val) { std::bitset<N> tmp(val); if(val < 0) tmp |= ~mask_ll; return tmp; }

        // Binary Add
        void bin_add(std::bitset<N>& result, std::bitset<N> a, std::bitset<N> b) {
            std::bitset<N> carry;
            while(b.any()) {
                // carry = (a & b) << 1; 
                // Breaking this out is faster as below.
                carry = a;
                carry &= b;
                carry <<= 1;
                a ^= b;
                b = std::move(carry);
            }
            result = std::move(a);
        }

        void bin_sub(std::bitset<N>& result, const std::bitset<N> lhs, const std::bitset<N> rhs) {
            bin_add(result, ~rhs, binary_one);
            bin_add(result, lhs, result);
        }

        // Multiply
        void bin_mult(std::bitset<N>& result, const std::bitset<N> lhs, const std::bitset<N> rhs) {
            std::bitset<N> add_result{};
            std::bitset<N> mult_result{};
 
            const int max_run = std::max(first_bit(lhs), first_bit(rhs));

            for(int i = 0; i <= max_run ; i++) {
                if(lhs[i]) {
                    // mult_result (rhs << i)
                    // Breaking this out below is faster.
                    mult_result = rhs;
                    mult_result <<= i;
                    bin_add(add_result, add_result, mult_result);
                }
            }
            result = std::move(add_result);
        }

        // Binary Divide
        void bin_div(std::bitset<N>& result, const std::bitset<N>& num, const std::bitset<N>& div) {

            try {
                if(div.none()) throw 0;
            } catch(...) {
                std::cerr << "Division by zero exception thrown." << std::endl;
                throw;
            }

            int bc_result = binary_compare(num, div);
            if(bc_result == -1) { result.reset(); return; }
            if(bc_result ==  0) { result = binary_one; return; }

            bool negate = (is_negative(num) || is_negative(div)) && !(is_negative(num) && is_negative(div));

            std::bitset<N> abs_num = abs(num);
            std::bitset<N> abs_div = abs(div);

            int fb_num = first_bit(abs_num);
            int fb_div = first_bit(abs_div);

            std::bitset<N> quotient{};
            std::bitset<N> remainder = abs_num;

            for(int i = fb_num - fb_div; i >= 0; i--) {
                std::bitset<N> div_shift = (abs_div << i);
                if(binary_compare(div_shift, abs_num) < 0) {
                    bin_sub(remainder, remainder, div_shift);
                    if(binary_compare(remainder, binary_zero) >= 0) {
                        quotient |= (binary_one << i);
                    } else {
                        bin_add(remainder, remainder, div_shift);
                    }
                } 
            }
            if(negate) bin_add(result, ~quotient, binary_one);
            else result = std::move(quotient);
        }

        // Binary negative check
        bool is_negative(std::bitset<N> val) {
            return(val[val.size() - 1]);
        }

        // Return the absolute value 
        std::bitset<N> abs(std::bitset<N> val) {
            if(is_negative(val)) {
                bin_add(val, ~val, binary_one);
            }
            return val;
        }

        // Binary first bit: 0001010001 left->right returns 3
        int first_bit(const std::bitset<N>& set) {
             for(int i = static_cast<int>(set.size()); i-- > 0;) {
                if(set[i]) return i;
            }
            return -1;
        }

        // Binary greater/equal/less than (lhs > rhs)
        int binary_compare(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
            if(!is_negative(lhs) && is_negative(rhs)) return  1;
            if(is_negative(lhs) && !is_negative(rhs)) return -1;

            // Loop until either 1 > 0 or 0 < 1 is found
            for(int i = static_cast<int>(rhs.size()); i-- > 0;) {
                if(lhs[i] != rhs[i]) return  (lhs[i] - rhs[i]);
            }
            return 0;
        }

        /////////////////////////////////////
        // For dec -> bin conversion
        /////////////////////////////////////

        std::string div2(std::string& dec_value) {

            int carry{};
            int adder{};
            std::string remainder{};

            for(auto& ch : dec_value) {
                carry = (ch - '0') / 2 + adder;
                adder = SX_THE_ODDS[(ch - '0')] * 5;
                remainder += '0' + carry;
            }
            remainder.erase(0, remainder.find_first_not_of('0'));
            return remainder;
        }

        std::bitset<N> decstr2binary(std::string dec_value) {

            bool neg = false;
            if(dec_value.length()) {

                if(dec_value[0] == '-') { neg = true; dec_value.erase(0, 1); }
     
                if(!std::ranges::all_of(dec_value.begin(), dec_value.end(), [](char c) { return isdigit(c) != 0; })) {
                    std::cerr << "Passed value string contains non-numeric values" << std::endl;
                    return binary_zero;            
                }
               
                if(dec_value.length()) { // We check again in case a "-" was passed only.
                    std::bitset<N> result;
                    std::string remainder{};
                    int end_digit = 0;
                    int pos = 0;

                    if(dec_value != "0") {
                        while(dec_value.length()) {
                            end_digit = dec_value[dec_value.length() - 1] - '0';
                            result[pos++] = SX_THE_ODDS[end_digit];
                            dec_value = div2(dec_value);
                        }
                    }

                    if(neg) bin_add(result, ~result, std::bitset<N>(1));
                    return result;
                }
            }
            return binary_zero;
        } 

        /////////////////////////////////////
        // For bin -> dec conversion
        /////////////////////////////////////

        std::string to_decimal(std::bitset<N> value, unsigned int convert_to_base = 10) {
            bool negative = (value[value.size() - 1]);

            if(negative) {
                // value.flip();
                bin_add(value, ~value, std::bitset<N>(1));
            }

            std::string result{};

            do {
                unsigned int remainder{};
                std::bitset<N> division; // Temp holder of divide value

                // Do the division
                for(int i = static_cast<int>(value.size()); i-- > 0;) {

                    // Calculate the remainder
                    remainder = remainder * 2 + value[i];

                    // If we have a overflow (e.g. number is bigger than base)
                    if (remainder >= convert_to_base) {
                        remainder -= convert_to_base;
                        division[i] = 1;
                    } else {
                        division[i] = 0;
                    }
                } 
                value = division;
                result.insert(0, 1, '0' + remainder);

            } while (value.any());

            return (negative ? "-" + result : result);
        }

    private:

        friend sxMegaInt;
        std::bitset<N> mValue{};

};
