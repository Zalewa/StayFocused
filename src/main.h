#ifndef idfdbf7a7a_8296_4f42_abe1_002c8a44b145
#define idfdbf7a7a_8296_4f42_abe1_002c8a44b145

class Main
{
public:
    Main(int argc, char **argv)
        : argc(argc), argv(argv)
    {
    }

    int run();

private:
    int argc;
    char **argv;
};

#endif
