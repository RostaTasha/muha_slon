#include<vector>

double sum4(std::vector<double> &v){double sum = 0;
    double c = 0;
    int size = v.size();
    for (int i =0; i < size; i++) {
        double y = v[i] - c;
        double t = sum + y;
        c = (t - sum) -y;
        sum = t;
    }
    return sum;
}

