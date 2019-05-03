#include "cypher.h"
#include "simplecrypt.h"

static QString temp;

QString & enc(const QString& plain)
{
  SimpleCrypt crypto(Q_UINT64_C(0x08836442e32f626d5));
  temp = crypto.encryptToString(plain);
  return temp;
}

QString & dec(const QString &coded)
{
   SimpleCrypt crypto(Q_UINT64_C(0x08836442e32f626d5));
   temp = crypto.decryptToString(coded);
   return temp;
}
