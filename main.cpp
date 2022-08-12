#include "sxMegaInt.h"

int main() {

    const int bit_size = 1024;

    sxMegaInt<bit_size> ans("13");
    std::cout << "SHOULD BE: 13" << std::endl;
    std::cout << "D-ANSWER: " << ans.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans.to_llong() << "\n\n";

    sxMegaInt<bit_size> ans2("-17");
    std::cout << "SHOULD BE: -17" << std::endl;
    std::cout << "D-ANSWER: " << ans2.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans2.to_llong() << "\n\n";

    sxMegaInt<bit_size> neg_mult = ans * ans2;
    std::cout << "SHOULD BE: -221" << std::endl;
    std::cout << "D-ANSWER: " << neg_mult.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << neg_mult.to_llong() << "\n\n";

    sxMegaInt<bit_size> ans3(13);
    std::cout << "SHOULD BE: 13" << std::endl;
    std::cout << "D-ANSWER: " << ans3.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans3.to_llong() << "\n\n";
 
    sxMegaInt<bit_size> ans4(-17);
    std::cout << "SHOULD BE: -17" << std::endl;
    std::cout << "D-ANSWER: " << ans4.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans4.to_llong() << "\n\n";
 
    ans += ans2;
    std::cout << "SHOULD BE: -4" << std::endl;
    std::cout << "D-ANSWER: " << ans.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans.to_llong() << "\n\n";

    ans3 += ans4;
    std::cout << "SHOULD BE: -4" << std::endl;
    std::cout << "D-ANSWER: " << ans3.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans3.to_llong() << "\n\n";

    ans3 += 30;
    std::cout << "SHOULD BE: 26" << std::endl;
    std::cout << "D-ANSWER: " << ans3.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans3.to_llong() << "\n\n";

    ans3 -= 15;
    std::cout << "SHOULD BE: 11" << std::endl;
    std::cout << "D-ANSWER: " << ans3.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans3.to_llong() << "\n\n";

    ans3 *= 3;
    std::cout << "SHOULD BE: 33" << std::endl;
    std::cout << "D-ANSWER: " << ans3.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans3.to_llong() << "\n\n";

    ans3 /= 11;
    std::cout << "SHOULD BE: 3" << std::endl;
    std::cout << "D-ANSWER: " << ans3.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans3.to_llong() << "\n\n";

    sxMegaInt<bit_size> ans5 = std::string("123");
    std::cout << "SHOULD BE: 123" << std::endl;
    std::cout << "D-ANSWER: " << ans5.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans5.to_llong() << "\n\n";

    ans5 /= 20;
    std::cout << "SHOULD BE: 6" << std::endl;
    std::cout << "D-ANSWER: " << ans5.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans5.to_llong() << "\n\n";

    sxMegaInt<bit_size> ans6 = 7550;
    std::cout << "SHOULD BE: 7550" << std::endl;
    std::cout << "D-ANSWER: " << ans6.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans6.to_llong() << "\n\n";

    ans6 /= -20;
    std::cout << "SHOULD BE: -377" << std::endl;
    std::cout << "D-ANSWER: " << ans6.to_decstring() << std::endl;
    std::cout << "L-ANSWER: " << ans6.to_llong() << "\n\n";

    sxMegaInt<bit_size> ans7 = 2;
    for(int i = 0; i < 100; i++) {
        ans6 = ans7.power(i);
        std::cout << "2^" << std::to_string(i) << ": " << ans6.to_decstring() << std::endl;
    }
    std::cout << "\n";

    ans7 = "123123132131";
    std::cout << "STRING ASSIGN EXPECTED: 123123132131 " << "\n";
    std::cout << "D-ANSWER: " << ans7.to_decstring() << "\n\n";

    ans7 += "123123132131";
    std::cout << "STRING += EXPECTED: 24624664262 " << std::endl;
    std::cout << "D-ANSWER: " << ans7.to_decstring() << "\n\n";

    sxMegaInt<2048> ans8 = 300;
    for(int i = 299; i > 0; i--) {
        ans8 *= i; 
    }

    std::cout << "FACTORIAL 300! " << std::endl;
    std::cout << "D-ANSWER: " << ans8.to_decstring() << "\n\n";

    std::cout << "FACTORIAL 300! OVERFLOW LONG LONG" << "\n";
    try {
        std::cout << ans8.to_llong() << "\n";
    } catch(...) {
        std::cerr << "Yup, caught!" << "\n\n";
    }

    try {
        std::cout << "EXPECTED: THROW DIVIDE BY ZERO." << "\n";
        ans6 /= 0; // Divide by zero throw
    } catch(...) {
        std::cerr << "Yup, caught!" << "\n\n";
    }

    return 0;
}
