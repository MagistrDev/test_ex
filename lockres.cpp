#include <mutex>

class LockRes
{
   std::mutex m;
   public:
       LockRes()
       {
           m.lock();
           catchRes();
       };
       ~LockRes()
       {
           releaseRes();
           m.unlock();
       }
};
