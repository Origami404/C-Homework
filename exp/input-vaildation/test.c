#include <iva.h>

int main() {
    accept_i8_relentless(.prompt = "Please input ...");

    accept_i8_relentless(
        .prompt = "Please input ...", 
        .at_fail = "Input fail, please");

    accept_i8_relentless(
        .prompt = "Please input ...",
        .at_fail = "Input fail, please ...",
        .file = stdout);
        
}