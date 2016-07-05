const MAXAVGSIZE = 200;
struct input_data {
    double input_data<200>;
};

program AVERAGEPROG {
    version AVERAGEVERS {
        double AVERAGE(input_data) = 1;
        double MEDIAN(input_data) = 2;
    } = 2;
    version AVERAGEVERSOLD {
        double AVERAGE(input_data) = 1;
    } = 1;
} = 22855;
