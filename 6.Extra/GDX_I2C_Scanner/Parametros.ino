extern "C" char* sbrk(int incr);
float freeRam() {
  //char top;
  char top = 't';
  return &top - reinterpret_cast<char*>(sbrk(0));
}


