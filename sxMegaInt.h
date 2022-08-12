#include <iostream>
#include <algorithm>
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
        sxMegaInt& operator=(const long long& val)    { mValue = std::bitset<N>(val); if(val < 0) mValue |= ~mask_ll; return *this; }

        sxMegaInt& operator+(const sxMegaInt& rhs)    { sxMegaInt nset = *this; nset.bitadd(rhs); return nset; }
        sxMegaInt& operator+(const long long& rhs)    { sxMegaInt nset = *this; nset.bitadd(std::bitset<N>(rhs)); return nset; }
        sxMegaInt& operator+(const std::string& rhs)  { sxMegaInt nset = *this; nset.bitadd(decstr2binary(rhs));  return nset; }
        sxMegaInt& operator+=(const sxMegaInt& rhs)   { bitadd(rhs); return *this;  }
        sxMegaInt& operator+=(const long long& rhs)   { bitadd(std::bitset<N>(rhs)); return *this; }
        sxMegaInt& operator+=(const std::string& rhs) { bitadd(decstr2binary(rhs)); return *this; }
        sxMegaInt& operator++() { bitadd(binary_one); return *this; }

        sxMegaInt& operator-(const sxMegaInt& rhs)    { sxMegaInt nset = *this; nset.bitsub(rhs); return nset; }
        sxMegaInt& operator-(const long long& rhs)    { sxMegaInt nset = *this; nset.bitsub(std::bitset<N>(rhs)); return nset; }
        sxMegaInt& operator-(const std::string& rhs)  { sxMegaInt nset = *this; nset.bitsub(decstr2binary(rhs)); return nset; }
        sxMegaInt& operator-=(const sxMegaInt& rhs)   { bitsub(rhs); return *this;  }
        sxMegaInt& operator-=(const long long& rhs)   { bitsub(std::bitset<N>(rhs)); return *this; }
        sxMegaInt& operator-=(const std::string& rhs) { bitsub(decstr2binary(rhs)); return *this; }
        sxMegaInt& operator--() { bitminus(binary_one); return *this; }

        sxMegaInt& operator*(const sxMegaInt& rhs)    { sxMegaInt nset = *this; nset.bitmult(rhs); return nset; }
        sxMegaInt& operator*(const long long& rhs)    { sxMegaInt nset = *this; nset.bitmult(std::bitset<N>(rhs)); return nset; }
        sxMegaInt& operator*(const std::string& rhs)  { sxMegaInt nset = *this; nset.bitmult(decstr2binary(rhs)); return nset; }
 
        sxMegaInt& operator*=(const sxMegaInt& rhs)   { bitmult(rhs); return *this; }
        sxMegaInt& operator*=(const long long& rhs)   { bitmult(std::bitset<N>(rhs)); return *this; }
        sxMegaInt& operator*=(const std::string& rhs) { bitmult(decstr2binary(rhs)); return *this; }

        sxMegaInt& operator/(const sxMegaInt& rhs)    { sxMegaInt nset = *this; nset.bitdiv(rhs); return nset; }
        sxMegaInt& operator/(const long long& rhs)    { sxMegaInt nset = *this; nset.bitdiv(std::bitset<N>(rhs)); return nset; }
        sxMegaInt& operator/(const std::string& rhs)  { sxMegaInt nset = *this; nset.bitdiv(decstr2binary(rhs)); return nset; }
 
        sxMegaInt& operator/=(const sxMegaInt& rhs)   { bitdiv(rhs); return *this; }
        sxMegaInt& operator/=(const long long& rhs)   { std::bitset<N> v(rhs); if(rhs < 0) v |= ~mask_ll; bitdiv(v); return *this; }
        sxMegaInt& operator/=(const std::string& rhs) { bitdiv(decstr2binary(rhs)); return *this; }

        bool operator==(const sxMegaInt& rhs)         { return binary_compare(mValue, rhs.mValue) == 0; }
        bool operator==(const long long& rhs)         { return binary_compare(mValue, std::bitset<N>(rhs)) == 0;  }
        bool operator==(const std::string& rhs)       { return binary_compare(mValue, decstr2binary(rhs)); }

        bool operator>(const sxMegaInt& rhs)          { return binary_compare(mValue, rhs.mValue) == 1; }
        bool operator>(const long long& rhs)          { return binary_compare(mValue, std::bitset<N>(rhs)) == 1;  }
        bool operator>(const std::string& rhs)        { return binary_compare(mValue, decstr2binary(rhs)) == 1; }

        bool operator>=(const sxMegaInt& rhs)         { return binary_compare(mValue, rhs.mValue) >= 0; }
        bool operator>=(const long long& rhs)         { return binary_compare(mValue, std::bitset<N>(rhs)) >= 0;  }
        bool operator>=(const std::string& rhs)       { return binary_compare(mValue, decstr2binary(rhs)) >= 0; }

        bool operator<(const sxMegaInt& rhs)          { return binary_compare(mValue, rhs.mValue) == -1; }
        bool operator<(const long long& rhs)          { return binary_compare(mValue, std::bitset<N>(rhs)) == -1;  }
        bool operator<(const std::string& rhs)        { return binary_compare(mValue, decstr2binary(rhs)) == -1; }

        bool operator<=(const sxMegaInt& rhs)         { return binary_compare(mValue, rhs.mValue) <= 0; }
        bool operator<=(const long long& rhs)         { return binary_compare(mValue, std::bitset<N>(rhs)) <= 0;  }
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

        // Binary Add
        void bitadd(const sxMegaInt<N>& other) { bitadd(other.mValue); }
        void bitadd(const std::bitset<N>& other) { mValue = bitadd(mValue, other); }
        std::bitset<N> bitadd(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
            std::bitset<N> a = lhs;
            std::bitset<N> b = rhs;
            std::bitset<N> carry;

            while(b != 0) {
                carry = (a & b) << 1;
                a = a ^ b;
                b = carry;
            }
            return a;
        }

        void fast_add(std::bitset<N>& result, std::bitset<N> a, std::bitset<N> b) {
            std::bitset<N> carry;
            while(b != 0) {
                carry = (a & b) << 1;
                a = a ^ b;
                b = carry;
            }
            result = a;
        }

        // Binary Subtract
        void bitsub(const sxMegaInt<N>& other) { bitsub(other.mValue); }
        void bitsub(const std::bitset<N>& other) { mValue = bitsub(mValue, other); }
        std::bitset<N> bitsub(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
            std::bitset<N> result = bitadd(~rhs, binary_one);
            return bitadd(lhs, result);
        }

        // Binary Multiply
        void bitmult(const sxMegaInt<N>& other) { bitmult(other.mValue); }
        void bitmult(const std::bitset<N>& other) { mValue = bitmult(mValue, other); }
        std::bitset<N> bitmult(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
            std::bitset<N> this_set = mValue;
            std::bitset<N> add_result; 

            int max_run = std::max(first_bit(lhs), first_bit(rhs));

            for(int i = 0; i <= max_run ; i++) {
                std::bitset<N> mult_result; 
                if(this_set[i]) {
                    mult_result = rhs;
                    mult_result <<= i;
                    fast_add(add_result, add_result, mult_result);
                }
            }
            return add_result;
        }

        // Binary Divide
        void bitdiv(const sxMegaInt<N>& divisor) { bitdiv(divisor.mValue); }
        void bitdiv(const std::bitset<N>& divisor) { mValue = bitdiv(mValue, divisor); }
        std::bitset<N> bitdiv(const std::bitset<N>& num, std::bitset<N> div) {
            int result = binary_compare(num, div);

            if(result == -1) return binary_zero; 
            if(result ==  0) return binary_one;

            try {
                if(binary_compare(div, binary_zero) == 0) throw 0;
            } catch(...) {
                std::cerr << "Division by zero exception thrown." << std::endl;
                throw;
            }

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
                    remainder = bitsub(remainder, div_shift);
                    if(binary_compare(remainder, binary_zero) >= 0) {
                        quotient |= (binary_one << i);
                    } else {
                        remainder = bitadd(remainder, div_shift);
                    }
                } 
            }
            return (negate ? bitadd(~quotient, binary_one) : quotient);
        }

        // Binary negative check
        bool is_negative(std::bitset<N> val) {
            return(val[val.size() - 1]);
        }

        // Return the absolute value 
        std::bitset<N> abs(std::bitset<N> val) {
            if(is_negative(val)) {
                val = bitadd(~val, binary_one);
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

                    if(dec_value.length()) {
                        if(dec_value != "0") {
                            while(dec_value.length()) {
                                end_digit = dec_value[dec_value.length() - 1] - '0';
                                result[pos++] = SX_THE_ODDS[end_digit];
                                dec_value = div2(dec_value);
                            }
                        }
                    }

                    if(neg) {
                        result.flip();
                        result = bitadd(result, std::bitset<N>(1));
                    }

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
                value.flip();
                value = bitadd(value, std::bitset<N>(1));
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
