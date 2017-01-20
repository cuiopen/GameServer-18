#ifndef _CommonDefine_H
#define _CommonDefine_H

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	do { delete (x); (x) = nullptr; } while(false)
#endif

#endif // _CommonDefine_H

