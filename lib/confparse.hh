#ifndef CONFPARSE_HH
#define CONFPARSE_HH
#include "string.hh"
#include "vector.hh"
class ErrorHandler;
#ifndef CLICK_TOOL
class Element;
# define CP_VA_PARSE_ARGS_REST Element *, ErrorHandler *, ...
#else
# define CP_VA_PARSE_ARGS_REST ErrorHandler *, ...
#endif

bool cp_eat_space(String &);
bool cp_is_space(const String &);

// argument lists <-> lists of arguments
String cp_subst(const String &);
String cp_unsubst(const String &);
void cp_argvec(const String &, Vector<String> &);
String cp_unargvec(const Vector<String> &);
String cp_argprefix(const String &, int);
void cp_spacevec(const String &, Vector<String> &);

// numbers
bool cp_bool(String, bool &, String *rest = 0);
bool cp_integer(String, int &, String *rest = 0);
bool cp_integer(String, int base, int &, String *rest = 0);
bool cp_real(const String &, int frac_digits, int &, int &, String *rest = 0);
int cp_real2(const String &, int frac_bits, int &, String *rest = 0);

// network addresses
bool cp_ip_address(String, unsigned char *, String *rest = 0);
bool cp_ethernet_address(const String &, unsigned char *, String *rest = 0);
#ifndef CLICK_TOOL
class IPAddress; class EtherAddress;
bool cp_ip_address(String, IPAddress &, String *rest = 0);
bool cp_ethernet_address(String, EtherAddress &, String *rest = 0);
#endif

#ifdef HAVE_IPSEC
bool cp_des_cblock(const String &, unsigned char *, String *rest = 0);
#endif

enum CpVaParseCmd {
  cpEnd = 0,
  cpOptional,
  cpIgnoreRest,
  cpLastControl,
  cpIgnore,
  cpBool,	// bool *value
  cpByte,	// unsigned char *value
  cpInteger,	// int *value
  cpUnsigned,	// int *value
  cpReal,	// int frac_digits, int *int_value, int *frac_value
  cpNonnegReal,	// int frac_digits, int *int_value, int *frac_value
  cpNonnegReal2,// int frac_bits, int *value
  cpInterval,	// int *value_milliseconds
  cpString,	// String *value
  cpIPAddress,	// unsigned char value[4] (or IPAddress *, or unsigned int *)
  cpEthernetAddress, // unsigned char value[6] (or EtherAddress *)
  cpElement,	// Element **value
  cpDesCblock,  // unsigned char value[8]
};

int cp_va_parse(const String &arg, CP_VA_PARSE_ARGS_REST);
int cp_va_parse(Vector<String> &args, CP_VA_PARSE_ARGS_REST);
int cp_va_space_parse(const String &arg, CP_VA_PARSE_ARGS_REST);
// ... is: cpEnd				stop
//     or: cpOptional				remaining args are optional
//     or: CpVaParseCmd type_id,		actual argument
//		const char *description,
//		[[from table above; usually T *value_store]]
// cp_va_parse stores no values in the value_store arguments
// unless it succeeds.

String cp_unparse_real(int, int frac_bits);
String cp_unparse_ulonglong(unsigned long long, int base, bool uppercase);

void cp_argvec_2(const String &, Vector<String> &, bool);

inline void
cp_argvec(const String &s, Vector<String> &vec)
{
  cp_argvec_2(s, vec, true);
}

#undef CP_VA_ARGS_REST
#endif
