#include "patch.h"

#include <QByteArray>

template <typename T>
void replace(QByteArray &ba, const T &before, const T &after)
{
  ba.replace(reinterpret_cast<const char*>(&before),sizeof(before),
             reinterpret_cast<const char*>(&after),sizeof(after));
}

QByteArray patched(QByteArray ba)
{
  // %%% REPLACE NAME %%%
  /* Name cannot be replaced because the new version identifies itself
   * as OVR0002.
  replace(ba, L"OVR0002", L"RZS0002");
  replace(ba, L"OVR0001", L"RZS0002");
  // %%% REPLACE PART OF THE NAME USED IN CONDITIONS %%%*
  replace(ba, L"OVR000", L"RZS000");
  */

  // %%% REPLACE SCREEN SIZE %%%
  replace(ba, 0.12096f, 0.1296f);
  replace(ba, 0.06804f, 0.0729f);

  replace(ba, 0.14976f, 0.1296f);
  replace(ba, 0.0936f , 0.0729f);

  replace(ba, 0.0756f , 0.0729f);

  // %%% REPLACE SCREEN RESOLUTION %%%
  /* Cannot replace the resolution - display not detected with some games
  replace(ba, 1280, 1920);
  replace(ba, 800, 1080);
  */

  return ba;
}
