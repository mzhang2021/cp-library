// Source: Competitive Programming 3

string AtoR(int A) {
    map<int, string> cvt;
    cvt[1000] = "M"; cvt[900] = "CM"; cvt[500] = "D"; cvt[400] = "CD";
    cvt[100] = "C"; cvt[90] = "XC"; cvt[50] = "L"; cvt[40] = "XL";
    cvt[10] = "X"; cvt[9] = "IX"; cvt[5] = "V"; cvt[4] = "IV";
    cvt[1] = "I";
    // process from larger values to smaller values
    string ret;
    for (map<int, string>::reverse_iterator i = cvt.rbegin(); i != cvt.rend(); i++)
        while (A >= i->first) {
            ret += i->second;
            A -= i->first; }
    return ret;
}

int RtoA(string R) {
    map<char, int> RtoA;
    RtoA['I'] = 1; RtoA['V'] = 5; RtoA['X'] = 10; RtoA['L'] = 50;
    RtoA['C'] = 100; RtoA['D'] = 500; RtoA['M'] = 1000;
    int value = 0;
    for (int i = 0; i < (int) R.size(); i++)
        if (R[i+1] && RtoA[R[i]] < RtoA[R[i+1]]) { // check next char first
            value += RtoA[R[i + 1]] - RtoA[R[i]]; // by definition
            i++; } // skip this char
        else value += RtoA[R[i]];
    return value;
}
