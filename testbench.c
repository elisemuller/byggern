// Test funksjon

int testbench(){
    int fatalCnt = 0;
    int errorCnt = 0;
    int warningCnt = 0;

    // kjør sram_test() men hent ut antall errors som returnverdi ellerno, behold prints innad i sramtest
    // errorCnt += sram_test();

    // kjør de andre testene på samme måte. De må altså:
    // printe HVA modulen feiler på
    // returnere antall fatals, errors og warnings (som et array?: a = [fatal, error, warning])
    
    printf('+--------------------------+\r\n');
    printf('| Self test finished with  |\r\n');
    printf('+--------------------------+\r\n');
    printf('| %d fatals                 |\r\n', fatalCnt);
    printf('| %d errors                 |\r\n', errorCnt);
    printf('| %d warnings               |\r\n', warningCnt);
    printf('+--------------------------+\r\n');

    if ((fatalCnt > 0) | (errorCnt > 10)){
        printf('#### Fatal errors discovered, aborting ####\r\n');
    }
    else{
        printf('#### Ready to proceed with BYGGERN!!! ####\r\n');
    }

    return fatalCnt;

}