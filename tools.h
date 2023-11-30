//
// Created by Salieri on 2023/10/17.
//

#include <limits>
#include <cstring>
#include <ctime>
#include <sys/timeb.h>
#include <algorithm>
#include <basetsd.h>

#ifndef SOLVER_ENCAPSULATION_TOOLS_H
#define SOLVER_ENCAPSULATION_TOOLS_H

#ifndef CbcDebug_H
#define CbcDebug_H
#endif

#define ZTE_DETAIL_PRINT(s) \
  {                          \
  }

// Smallest positive double value and Plus infinity (double and int)
#if 1
const double ZTE_DBL_MIN = (std::numeric_limits< double >::min)();
const double ZTE_DBL_MAX = (std::numeric_limits< double >::max)();
const int ZTE_INT_MAX = (std::numeric_limits< int >::max)();
const double ZTE_INT_MAX_AS_DOUBLE = (std::numeric_limits< int >::max)();
#else
#define ZTE_DBL_MIN (std::numeric_limits< double >::min())
#define ZTE_DBL_MAX (std::numeric_limits< double >::max())
#define ZTE_INT_MAX (std::numeric_limits< int >::max())
#define ZTE_INT_MAX_AS_DOUBLE (std::numeric_limits< int >::max())
#endif

#define CBC_HAS_CLP 1

/** Return the larger (according to <code>operator<()</code> of the arguments.
    This function was introduced because for some reason compiler tend to
    handle the <code>max()</code> function differently. */
template < class T >
inline T
ZteMax(const T x1, const T x2)
{
    return (x1 > x2) ? x1 : x2;
}

/** Return the smaller (according to <code>operator<()</code> of the arguments.
    This function was introduced because for some reason compiler tend to
    handle the min() function differently. */
template < class T >
inline T
ZteMin(const T x1, const T x2)
{
    return (x1 < x2) ? x1 : x2;
}

/** Return the absolute value of the argument. This function was introduced
    because for some reason compiler tend to handle the abs() function
    differently. */
template < class T >
inline T
ZteAbs(const T value)
{
    return value < 0 ? -value : value;
}

/*! \brief Return an array of length \p size filled with input from \p array,
  or null if \p array is null.
*/

template < class T >
inline T*
ZteCopyOfArray(const T* array, const int size)
{
    if (array) {
        T* arrayNew = new T[size];
        std::memcpy(arrayNew, array, size * sizeof(T));
        return arrayNew;
    }
    else {
        return NULL;
    }
}

/** This helper function fills an array with zero. For speed 8 entries
    are filled at a time. The array is given by a pointer to its first entry
    and its size.

    Note JJF - the speed claim seems to be false on IA32 so I have allowed
    for memset as an alternative */
template < class T >
inline void
ZteZeroN(T* to, const int size)
{
#ifdef USE_MEMCPY
    // Use memset - seems faster on Intel with gcc
#ifndef NDEBUG
  // Some debug so check
    if (size < 0)
        throw CoinError("trying to fill negative number of entries",
            "CoinZeroN", "");
#endif
    memset(to, 0, size * sizeof(T));
#else
    if (size == 0)
        return;

    /*#ifndef NDEBUG
        if (size < 0)
            throw CoinError("trying to fill negative number of entries",
                            "CoinZeroN", "");
    #endif*/
#if 1
    for (int n = size / 8; n > 0; --n, to += 8) {
        to[0] = 0;
        to[1] = 0;
        to[2] = 0;
        to[3] = 0;
        to[4] = 0;
        to[5] = 0;
        to[6] = 0;
        to[7] = 0;
    }
    switch (size % 8) {
        case 7:
            to[6] = 0;
        case 6:
            to[5] = 0;
        case 5:
            to[4] = 0;
        case 4:
            to[3] = 0;
        case 3:
            to[2] = 0;
        case 2:
            to[1] = 0;
        case 1:
            to[0] = 0;
        case 0:
            break;
    }
#else
    // Use Duff's device to fill
    CoinBigIndex n = (size + 7) / 8;
    --to;
    switch (size % 8) {
    case 0:
        do {
            *++to = 0;
    case 7:
        *++to = 0;
    case 6:
        *++to = 0;
    case 5:
        *++to = 0;
    case 4:
        *++to = 0;
    case 3:
        *++to = 0;
    case 2:
        *++to = 0;
    case 1:
        *++to = 0;
        } while (--n > 0);
    }
#endif
#endif
}

/** This helper function copies an array to another location using Duff's
    device (for a speedup of ~2). The arrays are given by pointers to their
    first entries and by the size of the source array. Overlapping arrays are
    handled correctly. */

template < class T >
inline void
ZteCopyN(const T* from, const int size, T* to)
{
    if (size == 0 || from == to)
        return;

    /*#ifndef NDEBUG
        if (size < 0)
            throw CoinError("trying to copy negative number of entries",
                            "CoinCopyN", "");
    #endif*/

    int n = (size + 7) / 8;
    if (to > from) {
        const T* downfrom = from + size;
        T* downto = to + size;
        // Use Duff's device to copy
        switch (size % 8) {
            case 0:
                do {
                    *--downto = *--downfrom;
                    case 7:
                        *--downto = *--downfrom;
                    case 6:
                        *--downto = *--downfrom;
                    case 5:
                        *--downto = *--downfrom;
                    case 4:
                        *--downto = *--downfrom;
                    case 3:
                        *--downto = *--downfrom;
                    case 2:
                        *--downto = *--downfrom;
                    case 1:
                        *--downto = *--downfrom;
                } while (--n > 0);
        }
    }
    else {
        // Use Duff's device to copy
        --from;
        --to;
        switch (size % 8) {
            case 0:
                do {
                    *++to = *++from;
                    case 7:
                        *++to = *++from;
                    case 6:
                        *++to = *++from;
                    case 5:
                        *++to = *++from;
                    case 4:
                        *++to = *++from;
                    case 3:
                        *++to = *++from;
                    case 2:
                        *++to = *++from;
                    case 1:
                        *++to = *++from;
                } while (--n > 0);
        }
    }
}


/** An ordered pair. It's the same as std::pair, just this way it'll have the
    same look as the triple sorting. */
template < class S, class T >
struct ZtePair {
public:
    /// First member of pair
    S first;
    /// Second member of pair
    T second;

public:
    /// Construct from ordered pair
    ZtePair(const S& s, const T& t)
            : first(s)
            , second(t)
    {
    }
};

/**@name Comparisons on first element of two ordered pairs */
//@{
/** Function operator.
    Returns true if t1.first &lt; t2.first (i.e., increasing). */
template < class S, class T >
class ZteFirstLess_2 {
public:
    /// Compare function
    inline bool operator()(const ZtePair< S, T >& t1,
                           const ZtePair< S, T >& t2) const
    {
        return t1.first < t2.first;
    }
};

template < class S, class T, class CoinCompare2 >
void ZteSort_2(S* sfirst, S* slast, T* tfirst, const CoinCompare2& pc)
{
    const size_t len = coinDistance(sfirst, slast);
    if (len <= 1)
        return;

    typedef ZtePair< S, T > ST_pair;
    ST_pair* x = static_cast<ST_pair*>(::operator new(len * sizeof(ST_pair)));
#ifdef ZEROFAULT
    // Can show RUI errors on some systems due to copy of ST_pair with gaps.
  // E.g., <int, double> has 4 byte alignment gap on Solaris/SUNWspro.
    memset(x, 0, (len * sizeof(ST_pair)));
#endif

    size_t i = 0;
    S* scurrent = sfirst;
    T* tcurrent = tfirst;
    while (scurrent != slast) {
        new (x + i++) ST_pair(*scurrent++, *tcurrent++);
    }

    std::sort(x, x + len, pc);

    scurrent = sfirst;
    tcurrent = tfirst;
    for (i = 0; i < len; ++i) {
        *scurrent++ = x[i].first;
        *tcurrent++ = x[i].second;
    }

    ::operator delete(x);
}

template < class S, class T >
void ZteSort_2(S* sfirst, S* slast, T* tfirst)
{
    ZteSort_2(sfirst, slast, tfirst, ZteFirstLess_2< S, T >());
}


inline double ZteGetTimeOfDay()
{
#ifdef COIN_DOING_DIFFS
    // when trying to see differences between runs it can be helpful
    return 0.0;
#endif
    struct _timeb timebuffer;
#pragma warning(disable : 4996)
    _ftime(&timebuffer); // C4996
#pragma warning(default : 4996)
    return timebuffer.time + timebuffer.millitm / 1000.0;
}

static inline double ZteCpuTime()
{
#ifdef COIN_DOING_DIFFS
    // when trying to see differences between runs it can be helpful
    return 0.0;
#endif
    double cpu_temp;
#if defined(_MSC_VER) || defined(__MSVCRT__)
#ifdef HAVE_SDK
    FILETIME creation;
    FILETIME exit;
    FILETIME kernel;
    FILETIME user;
    GetProcessTimes(GetCurrentProcess(), &creation, &exit, &kernel, &user);
    double t = user.dwHighDateTime * TWO_TO_THE_THIRTYTWO + user.dwLowDateTime;
    return t / 10000000.0;
#else
    unsigned int ticksnow; /* clock_t is same as int */
    ticksnow = (unsigned int)clock();
    cpu_temp = (double)((double)ticksnow / CLOCKS_PER_SEC);
#endif

#else
    struct rusage usage;
#ifdef ZEROFAULT
    usage.ru_utime.tv_sec = 0;
    usage.ru_utime.tv_usec = 0;
#endif
    getrusage(RUSAGE_SELF, &usage);
    cpu_temp = static_cast<double>(usage.ru_utime.tv_sec);
    cpu_temp += 1.0e-6 * (static_cast<double>(usage.ru_utime.tv_usec));
#endif
    return cpu_temp;
}

/**
   Query the elapsed wallclock time since the first call to this function. If
   a positive argument is passed to the function then the time of the first
   call is set to that value (this kind of argument is allowed only at the
   first call!). If a negative argument is passed to the function then it
   returns the time when it was set.
*/
inline double ZteWallclockTime(double callType = 0)
{
    double callTime = ZteGetTimeOfDay();
    static const double firstCall = callType > 0 ? callType : callTime;
    return callType < 0 ? firstCall : callTime - firstCall;
}

static inline double ZteSysTime()
{
    double sys_temp;
#if defined(_MSC_VER) || defined(__MSVCRT__)
    sys_temp = 0.0;
#else
    struct rusage usage;
#ifdef ZEROFAULT
    usage.ru_utime.tv_sec = 0;
    usage.ru_utime.tv_usec = 0;
#endif
    getrusage(RUSAGE_SELF, &usage);
    sys_temp = static_cast<double>(usage.ru_stime.tv_sec);
    sys_temp += 1.0e-6 * (static_cast<double>(usage.ru_stime.tv_usec));
#endif
    return sys_temp;
}

// On most systems SELF seems to include children threads, This is for when it doesn't
static inline double ZteCpuTimeJustChildren()
{
    double cpu_temp;
#if defined(_MSC_VER) || defined(__MSVCRT__)
    cpu_temp = 0.0;
#else
    struct rusage usage;
#ifdef ZEROFAULT
    usage.ru_utime.tv_sec = 0;
    usage.ru_utime.tv_usec = 0;
#endif
    getrusage(RUSAGE_CHILDREN, &usage);
    cpu_temp = static_cast<double>(usage.ru_utime.tv_sec);
    cpu_temp += 1.0e-6 * (static_cast<double>(usage.ru_utime.tv_usec));
#endif
    return cpu_temp;
}

/*! \brief Return a random number between 0 and 1

  A platform-independent linear congruential generator. For a given seed, the
  generated sequence is always the same regardless of the (32-bit)
  architecture. This allows to build & test in different environments, getting
  in most cases the same optimization path.

  Set \p isSeed to true and supply an integer seed to set the seed
  (vid. #CoinSeedRandom)

  \todo Anyone want to volunteer an upgrade for 64-bit architectures?
*/
inline double ZteDrand48(bool isSeed = false, unsigned int seed = 1)
{
    static unsigned int last = 123456;
    if (isSeed) {
        last = seed;
    }
    else {
        last = 1664525 * last + 1013904223;
        return ((static_cast<double>(last)) / 4294967296.0);
    }
    return (0.0);
}

/** This helper function fills an array with a given value. For speed 8 entries
    are filled at a time. The array is given by a pointer to its first entry
    and its size.

    Note JJF - the speed claim seems to be false on IA32 so I have added
    CoinZero to allow for memset. */
template < class T >
inline void
ZteFillN(T* to, const int size, const T value)
{
    if (size == 0)
        return;

    /*#ifndef NDEBUG
        if (size < 0)
            throw CoinError("trying to fill negative number of entries",
                            "CoinFillN", "");
    #endif*/
#if 1
    for (int n = size / 8; n > 0; --n, to += 8) {
        to[0] = value;
        to[1] = value;
        to[2] = value;
        to[3] = value;
        to[4] = value;
        to[5] = value;
        to[6] = value;
        to[7] = value;
    }
    switch (size % 8) {
        case 7:
            to[6] = value;
            // fall through
        case 6:
            to[5] = value;
            // fall through
        case 5:
            to[4] = value;
            // fall through
        case 4:
            to[3] = value;
            // fall through
        case 3:
            to[2] = value;
            // fall through
        case 2:
            to[1] = value;
            // fall through
        case 1:
            to[0] = value;
            // fall through
        case 0:
            break;
    }
#else
    // Use Duff's device to fill
    int n = (size + 7) / 8;
    --to;
    switch (size % 8) {
    case 0:
        do {
            *++to = value;
    case 7:
        *++to = value;
    case 6:
        *++to = value;
    case 5:
        *++to = value;
    case 4:
        *++to = value;
    case 3:
        *++to = value;
    case 2:
        *++to = value;
    case 1:
        *++to = value;
        } while (--n > 0);
    }
#endif
}



class ThreadRandom {
public:
    /**@name Constructors, destructor */

    //@{
    /** Default constructor. */
    ThreadRandom()
    {
        seed_ = 12345678;
    }
    /** Constructor wih seed. */
    ThreadRandom(unsigned int seed)
    {
        seed_ = seed;
    }
    /** Destructor */
    ~ThreadRandom() = default;
    // Copy
    ThreadRandom(const ThreadRandom& rhs)
    {
        seed_ = rhs.seed_;
    }
    // Assignment
    ThreadRandom& operator=(const ThreadRandom& rhs)
    {
        if (this != &rhs) {
            seed_ = rhs.seed_;
        }
        return *this;
    }

    //@}

    /**@name Sets/gets */

    //@{
    /** Set seed. */
    inline void setSeed(unsigned int seed)
    {
        seed_ = seed;
    }
    /** Get seed. */
    inline unsigned int getSeed() const
    {
        return seed_;
    }
    /// return a random number
    inline double randomDouble() const
    {
        double retVal;
        seed_ = 1664525 * (seed_)+1013904223;
        retVal = ((static_cast<double>(seed_)) / 4294967296.0);
        return retVal;
    }
    /// make more random (i.e. for startup)
    inline void randomize(int n = 0)
    {
        if (!n)
            n = seed_ & 255;
        for (int i = 0; i < n; i++)
            randomDouble();
    }
    //@}

protected:
    /**@name Data members
       The data members are protected to allow access for derived classes. */
    //@{
    /// Current seed
    mutable unsigned int seed_;
    //@}
};

class ZteThreadRandom {
public:
    /**@name Constructors, destructor */

    //@{
    /** Default constructor. */
    ZteThreadRandom()
    {
        seed_ = 12345678;
    }
    /** Constructor wih seed. */
    ZteThreadRandom(unsigned int seed)
    {
        seed_ = seed;
    }
    /** Destructor */
    ~ZteThreadRandom() = default;
    // Copy
    ZteThreadRandom(const ZteThreadRandom& rhs)
    {
        seed_ = rhs.seed_;
    }
    // Assignment
    ZteThreadRandom& operator=(const ZteThreadRandom& rhs)
    {
        if (this != &rhs) {
            seed_ = rhs.seed_;
        }
        return *this;
    }

    //@}

    /**@name Sets/gets */

    //@{
    /** Set seed. */
    inline void setSeed(unsigned int seed)
    {
        seed_ = seed;
    }
    /** Get seed. */
    inline unsigned int getSeed() const
    {
        return seed_;
    }
    /// return a random number
    inline double randomDouble() const
    {
        double retVal;
        seed_ = 1664525 * (seed_)+1013904223;
        retVal = ((static_cast<double>(seed_)) / 4294967296.0);
        return retVal;
    }
    /// make more random (i.e. for startup)
    inline void randomize(int n = 0)
    {
        if (!n)
            n = seed_ & 255;
        for (int i = 0; i < n; i++)
            randomDouble();
    }
    //@}

protected:
    /**@name Data members
       The data members are protected to allow access for derived classes. */
    //@{
    /// Current seed
    mutable unsigned int seed_;
    //@}
};

/** This function figures out whether file names should contain slashes or
    backslashes as directory separator */
inline char ZteFindDirSeparator() {
    int size = 1000;
    char* buf = 0;
    while (true) {
        buf = new char[size];
        if (_getcwd(buf, size))
            break;
        delete[] buf;
        buf = 0;
        size = 2 * size;
    }
    // if first char is '/' then it's unix and the dirsep is '/'. otherwise we
    // assume it's dos and the dirsep is '\'
    char dirsep = buf[0] == '/' ? '/' : '\\';
    delete[] buf;
    return dirsep;
}

/** This helper function copies an array to another location. The two arrays
    must not overlap (otherwise an exception is thrown). For speed 8 entries
    are copied at a time. The arrays are given by pointers to their first
    entries and by the size of the source array.

    Note JJF - the speed claim seems to be false on IA32 so I have added
    alternative coding if USE_MEMCPY defined*/
template < class T >
inline void
ZteMemcpyN(const T* from, const LONG_PTR size, T* to)
{
#ifndef _MSC_VER
    #ifdef USE_MEMCPY
    // Use memcpy - seems a lot faster on Intel with gcc
#ifndef NDEBUG
  // Some debug so check
    if (size < 0)
        throw CoinError("trying to copy negative number of entries",
            "CoinMemcpyN", "");

#if 0
    /* There is no point to do this test. If to and from are from different
       blocks then dist is undefined, so this can crash correct code. It's
       better to trust the user that the arrays are really disjoint. */
    const long dist = to - from;
    if (-size < dist && dist < size)
        throw CoinError("overlapping arrays", "CoinMemcpyN", "");
#endif
#endif
    std::memcpy(to, from, size * sizeof(T));
#else
    if (size == 0 || from == to)
        return;

#ifndef NDEBUG
    if (size < 0)
        throw CoinError("trying to copy negative number of entries",
            "CoinMemcpyN", "");
#endif

#if 0
    /* There is no point to do this test. If to and from are from different
       blocks then dist is undefined, so this can crash correct code. It's
       better to trust the user that the arrays are really disjoint. */
    const long dist = to - from;
    if (-size < dist && dist < size)
        throw CoinError("overlapping arrays", "CoinMemcpyN", "");
#endif

    for (CoinBigIndex n = static_cast<CoinBigIndex>(size >> 3); n > 0; --n, from += 8, to += 8) {
        to[0] = from[0];
        to[1] = from[1];
        to[2] = from[2];
        to[3] = from[3];
        to[4] = from[4];
        to[5] = from[5];
        to[6] = from[6];
        to[7] = from[7];
    }
    switch (size % 8) {
    case 7:
        to[6] = from[6];
    case 6:
        to[5] = from[5];
    case 5:
        to[4] = from[4];
    case 4:
        to[3] = from[3];
    case 3:
        to[2] = from[2];
    case 2:
        to[1] = from[1];
    case 1:
        to[0] = from[0];
    case 0:
        break;
    }
#endif
#else
    ZteCopyN(from, size, to);
#endif
}

/** Returns strdup or NULL if original NULL */
inline char* ZteStrdup(const char* name)
{
    char* dup = NULL;
    if (name) {
        const int len = static_cast<int>(strlen(name));
        dup = static_cast<char*>(malloc(len + 1));
        ZteMemcpyN(name, len, dup);
        dup[len] = 0;
    }
    return dup;
}

class tools {

};


#endif //SOLVER_ENCAPSULATION_TOOLS_H

