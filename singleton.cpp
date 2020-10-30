class singleton
{
public:
  static singleton& instance() {
     static singleton inst;
     return inst;
  }
private:
 singleton() {}
};
