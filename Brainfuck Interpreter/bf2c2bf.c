#include <unistd.h>
unsigned char r[65536],*e=r;
int main(){
    *e+=3;
    while(*e){
        ++e;*e+=5;
        --(*(--e));
    }
    e+=2;
    ++*e;
    --e;
    while(*e){
        e+=2;
        *e+=4;
        ++e;
        *e+=2;
        ++e;
        *e+=5;
        ++e;
        *e+=5;
        ++e;
        ++*e;
        e+=2;
        ++*e;
        --e;
        *e+=2;
        while(*e){
            *e+=2;
            --e;
        }
        ++e;
        *e-=3;
    }
    ++e;
    *e+=4;
    write(1,e,1);
    e+=3;
    write(1,e,1);
    *e+=5;
    write(1,e,1);
    ++e;
    *e-=6;
    write(1,e,1);
    --e;
    *e-=2;
    write(1,e,1);
    *e+=9;
    write(1,e,1);
    ++e;
    ++*e;
    write(1,e,1);
    ++*e;
    write(1,e,1);
    e-=4;
    *e+=3;
    write(1,e,1);
    while(*e){
        ++e;
    }
    e-=2;
    write(1,e,1);
    e-=3;
    write(1,e,1);
    *e-=7;
    write(1,e,1);
    *(++e)+=4;
    write(1,e,1);
    *(--e)+=5;
    write(1,e,1);
    ++*e;
    write(1,e,1);
    *(++e)-=5;
    write(1,e,1);
    (*(++e))++;
    write(1,e,1);
    *(--e)+=4;
    write(1,e,1);
    e+=2;
    *e+=2;
    write(1,e,1);
    ++e;
    --*e;
    --*e;
    --*e;
    --*e;
    --*e;
    write(1,e,1);
    --e;
    --e;
    --e;
    --*e;
    --*e;
    --*e;
    --*e;
    --*e;
    write(1,e,1);
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    write(1,e,1);
    --*e;
    --*e;
    --*e;
    --*e;
    --*e;
    --*e;
    --*e;
    write(1,e,1);
    --e;
    --*e;
    --*e;
    write(1,e,1);
    --e;
    --e;
    --e;
    write(1,e,1);
    ++e;
    ++e;
    ++e;
    write(1,e,1);
    --e;
    --e;
    ++*e;
    write(1,e,1);
    ++e;
    --*e;
    --*e;
    --*e;
    --*e;
    --*e;
    --*e;
    write(1,e,1);
    --*e;
    write(1,e,1);
    write(1,e,1);
    --*e;
    --*e;
    write(1,e,1);
    ++*e;
    ++*e;
    ++*e;
    write(1,e,1);
    --*e;
    --*e;
    --*e;
    --*e;
    --*e;
    --e;
    ++*e;
    ++*e;
    write(1,e,1);
    --e;
    --*e;
    --*e;
    while(*e){
        ++e;
        ++*e;
        --e;
        --*e;
    }
    e+=5;
    --*e;
    --*e;
    write(1,e,1);
    --*e;
    --*e;
    write(1,e,1);
    --e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    write(1,e,1);
    ++e;
    ++e;
    --*e;
    write(1,e,1);
    --e;
    --e;
    --e;
    write(1,e,1);
    ++e;
    ++e;
    ++e;
    --*e;
    --*e;
    write(1,e,1);
    ++e;
    write(1,e,1);
    e-=4;
    --*e;
    --*e;
    --*e;
    --*e;
    --*e;
    write(1,e,1);
    ++e;
    --*e;
    --*e;
    --*e;
    --*e;
    write(1,e,1);
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    write(1,e,1);
    --*e;
    --*e;
    --*e;
    --*e;
    --e;
    ++*e;
    write(1,e,1);
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++*e;
    ++e;
    ++e;
    --*e;
    --*e;
    write(1,e,1);
    ++*e;
    write(1,e,1);
    ++*e;
    ++*e;
    --e;
    --e;
    --e;
    --e;
    write(1,e,1);
    while(*(e+1)) ++e;
    write(1,e,1);
    ++e;
    ++e;
    read(0,e,1);
    while(*e){
        ++e;
        ++e;
        ++*e;
        ++*e;
        ++*e;
        while(*e){
            --e;
            ++*e;
            ++*e;
            ++*e;
            ++*e;
            ++*e;
            ++*e;
            ++*e;
            ++e;
            --*e;
        }
        --e;
        while(*e){
            --e;
            while(*e){
                --*e;
                while(*e){
                    --*e;
                    --e;
                }
            }
            ++e;
            ++e;
            while(*e){
                ++e;
            }
            --e;
            --*e;
        }
        --e;
        while(*e){
            --e;
            ++*e;
            ++*e;
            ++*e;
            ++*e;
            ++*e;
            ++e;
            --*e;
            while(*e){
                --e;
                ++*e;
                ++*e;
                ++*e;
                ++e;
                --*e;
                while(*e){
                    --e;
                    --*e;
                    --*e;
                    ++e;
                    --*e;
                    while(*e){
                        --e;
                        ++*e;
                        ++*e;
                        ++*e;
                        ++e;
                        --*e;
                        while(*e){
                            --e;
                            ++*e;
                            ++*e;
                            ++*e;
                            ++*e;
                            while(*e){
                                ++e;
                                while(*e){
                                    --*e;
                                    ++e;
                                    ++e;
                                }
                                --e;
                                while(*e){
                                    ++e;
                                    ++e;
                                }
                                --e;
                                --e;
                                --*e;
                            }
                            ++e;
                            while(*e){
                                --e;
                                ++*e;
                                ++*e;
                                ++*e;
                                ++e;
                                --*e;
                                while(*e){
                                    --e;
                                    --*e;
                                    --*e;
                                    --*e;
                                    ++e;
                                    --*e;
                                    while(*e){
                                        --e;
                                        ++*e;
                                        ++*e;
                                        ++*e;
                                        ++*e;
                                        ++e;
                                        --*e;
                                    while(*e){
                                        --e;
                                        ++*e;
                                        ++*e;
                                        ++*e;
                                        while(*e){
                                            ++e;
                                            while(*e){
                                                --*e;
                                                while(*e){
                                                    --*e;
                                                    while(*e){
                                                        --*e;
                                                        while(*e){
                                                            --*e;
                                                            ++e;
                                                            ++e;
                                                        }
                                                    }
                                                }
                                            }
                                            --e;
                                            while(*e){
                                                ++e;
                                                ++e;
                                            }
                                            --e;
                                            --e;
                                            --*e;
                                        }
                                        ++e;
                                        while(*e){
                                            --e;
                                            ++*e;
                                            ++e;
                                            --*e;
                                            while(*e){
                                                --e;
                                                --*e;
                                                ++e;
                                                --*e;
                                                while(*e){
                                                    --e;
                                                    ++*e;
                                                    ++*e;
                                                    ++e;
                                                    --*e;
                                                    while(*e){
                                                        --e;
                                                        while(*e){
                                                            --*e;
                                                        }
                                                        ++e;
                                                        --*e;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    --e;
    while(*e){
        --*e;
        while(*e){
        --*e;
        while(*e){
        ++e;
        ++*e;
        --e;
        --*e;
        }
        ++e;
        }
        --e;
        while(*e){
        --e;
        --e;
        --e;
        --e;
        write(1,e,1);
        ++e;
        ++*e;
        ++*e;
        ++*e;
        write(1,e,1);
        ++*e;
        write(1,e,1);
        ++*e;
        ++*e;
        ++*e;
        write(1,e,1);
        --*e;
        --*e;
        --*e;
        --*e;
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        ++e;
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        ++*e;
        ++*e;
        write(1,e,1);
        --e;
        write(1,e,1);
        ++e;
        --*e;
        write(1,e,1);
        ++*e;
        ++*e;
        --e;
        --e;
        --e;
        --e;
        write(1,e,1);
        while(*e){
        ++e;
        }
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        }
        --e;
        while(*e){
        while(*e){
        --e;
        }
        ++e;
        ++*e;
        ++*e;
        write(1,e,1);
        --*e;
        --*e;
        while(*e){
        ++e;
        }
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        }
        --e;
        while(*e){
        --e;
        --e;
        ++*e;
        ++*e;
        write(1,e,1);
        write(1,e,1);
        --*e;
        --*e;
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        }
        --e;
        while(*e){
        --e;
        --e;
        write(1,e,1);
        write(1,e,1);
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        }
        --e;
        while(*e){
        --e;
        --e;
        write(1,e,1);
        write(1,e,1);
        --*e;
        write(1,e,1);
        ++*e;
        ++e;
        ++e;
        ++e;
        ++e;
        }
        --e;
        while(*e){
        --e;
        --e;
        ++*e;
        ++*e;
        write(1,e,1);
        write(1,e,1);
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        ++*e;
        ++e;
        ++e;
        ++e;
        }
        --e;
        while(*e){
        --e;
        --e;
        --e;
        write(1,e,1);
        ++e;
        ++e;
        write(1,e,1);
        ++e;
        ++e;
        ++e;
        ++e;
        ++e;
        }
        --e;
        while(*e){
        --e;
        --e;
        --e;
        --e;
        --*e;
        --*e;
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        ++*e;
        ++*e;
        ++*e;
        ++*e;
        ++*e;
        ++e;
        write(1,e,1);
        --*e;
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        ++*e;
        ++*e;
        ++*e;
        write(1,e,1);
        ++*e;
        ++e;
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        --e;
        --e;
        --e;
        --*e;
        write(1,e,1);
        while(*e){
        ++e;
        }
        ++e;
        }
        --e;
        while(*e){
        --e;
        --e;
        --e;
        --e;
        write(1,e,1);
        --*e;
        --*e;
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        ++e;
        ++*e;
        ++*e;
        ++*e;
        ++*e;
        write(1,e,1);
        --e;
        ++*e;
        ++*e;
        write(1,e,1);
        ++*e;
        ++*e;
        ++*e;
        ++e;
        --*e;
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        ++e;
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        --e;
        --e;
        --e;
        write(1,e,1);
        --*e;
        while(*e){
        ++e;
        }
        }
        --e;
        while(*e){
        --e;
        --e;
        --e;
        --e;
        --e;
        --*e;
        --*e;
        --*e;
        --*e;
        write(1,e,1);
        ++e;
        ++e;
        write(1,e,1);
        --e;
        --e;
        write(1,e,1);
        ++*e;
        ++*e;
        ++*e;
        ++*e;
        ++*e;
        write(1,e,1);
        ++e;
        ++e;
        ++e;
        ++*e;
        write(1,e,1);
        ++*e;
        ++*e;
        ++e;
        write(1,e,1);
        ++e;
        ++e;
        }
    --e;
    write(1,e,1);
    ++e;
    }
    ++e;
    read(0,e,1);
    }

}