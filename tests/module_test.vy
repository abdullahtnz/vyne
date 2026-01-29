module vcore;
module CustomModule;

os = vcore.platform();
version = vcore.version;

sub::CustomModule call(){
    log("hi");
};

log("Hello from " + os + "! Using Vyne version : " + version);
CustomModule.call();