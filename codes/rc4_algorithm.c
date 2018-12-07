unsigned char *rc4_key_calc(unsigned char * key){
    /*calculate key for rc4 algorithm*/
    int key_length = strlen(key);
    unsigned char * S = (unsigned char *)malloc(256);
    for (int i=0;i<256;++i){
        S[i] = i;
    }
    int j=0;
    char temp;
    for(int i=0;i<256;++i){
        j = (j+S[i]+key[(int)(i % key_length)]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
    return S;
}

unsigned int rc4_calc(unsigned char * S,unsigned char data){
    /*This is encryption and decryption algorithm both*/
    static int rc4_i=0;
    static int rc4_j=0;
    int out;
    char temp;
    unsigned int cipher;
    rc4_i = (rc4_i+1) % 256;
    rc4_j = (rc4_j+S[rc4_i]) % 256;
    temp = S[rc4_i];
    S[rc4_i] = S[rc4_j];
    S[rc4_j] = temp;
    out = S[(S[rc4_i]+S[rc4_j]) % 256];
    cipher = out ^(data);
    return cipher;
}

int main(int argc ,char ** argv){
    if(argc != 4){
        printf("USAGE: %s <password> <input_file> <output_file>",argv[0]);
        return 0;
    }
    unsigned char * key = argv[1];
    unsigned char * data_ptr = (unsigned char *)malloc(1);
    unsigned char * S = rc4_key_calc(key);
    FILE * inp_file = fopen(argv[2],"rb");
    if(inp_file == NULL){
        printf("Cant open input file %s",argv[2]);
        return (-1);
    }
    FILE * out_file = fopen(argv[3],"wb");
    if(out_file == NULL){
        printf("Cant open output file %s",argv[3]);
        return -1;
    }
    int c;
    while(!feof(inp_file)){
        if( (c=fgetc(inp_file)) != EOF){
            fputc(rc4_calc(S,(unsigned char)c),out_file);
        }
    }
    free(S);
    fclose(inp_file);
    fclose(out_file);

    /*
    //str2binary test
    char data[]= "salma";
    printf("%s\n",str2binary(data));
    */

    /*
    //rc4_encrypt and rc4_decrypt test
    char * message = "This is our secret message";
    char key[]= "thisismypasswordiuse4rc4";
    char * out = rc4_encrypt(message,key);
    printf("Original message:\n");
    printf("%s\n",message);
    printf("Key is: %s\n",key);
    printf("Encoding....\n");
    printf("Encoded Message:\n");
    printf("%s\n",out);
    printf("Decoding...\n");
    out = rc4_decrypt(out,key);
    printf("Decoded Message:\n");
    printf("%s\n",out);
    free(out);
    */
    return 0;
}