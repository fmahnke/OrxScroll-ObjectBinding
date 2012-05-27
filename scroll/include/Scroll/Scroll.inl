//! Constants
#ifndef __NO_SCROLLED__
static const orxSTRING szParamEditor = "-editor";
#endif // __NO_SCROLLED__

//! Code
template<class G>
G &Scroll<G>::GetInstance()
{
  if(!spoInstance)
  {
    spoInstance = new G();
  }

  return *ScrollCast<G *>(spoInstance);
}

template<class G>
ScrollObject *Scroll<G>::CreateObject(const orxSTRING _zModelName)
{
  // Calls base method
  return ScrollBase::CreateObject(_zModelName, ScrollObject::FlagRunTime);
}

template<class G>
void Scroll<G>::DeleteObject(ScrollObject *_poObject)
{
  // Calls base method
  ScrollBase::DeleteObject(_poObject);
}

template<class G>
orxSTATUS Scroll<G>::SetMapName(const orxSTRING _zMapName)
{
  orxSTATUS eResult;

  // Not in editor mode?
  if(!IsEditorMode())
  {
    // Calls base method
    eResult = ScrollBase::SetMapName(_zMapName);
  }
  else
  {
    // Updates result
    eResult = orxSTATUS_FAILURE;
  }

  // Done!
  return eResult;
}

template<class G>
const orxSTRING Scroll<G>::GetMapName() const
{
  // Calls base method
  return ScrollBase::GetMapName();
}

template<class G>
const orxSTRING Scroll<G>::GetMapShortName() const
{
  // Calls base method
  return ScrollBase::GetMapShortName();
}

template<class G>
orxSTATUS Scroll<G>::LoadMap()
{
  orxSTATUS eResult;

  // Not in editor mode?
  if(!IsEditorMode())
  {
    // Calls base method
    eResult = ScrollBase::LoadMap();
  }
  else
  {
    // Updates result
    eResult = orxSTATUS_FAILURE;
  }

  // Done!
  return eResult;
}

template<class G>
const orxSTRING Scroll<G>::GetEncryptionKey() const
{
  return "This is Scroll's default encryption key!";
}

template<class G>
void Scroll<G>::Execute(int argc, char **argv)
{
#ifndef __NO_SCROLLED__
  orxBOOL bEditor = orxFALSE;

  // For all params
  for(int i = 0; !bEditor && (i < argc); i++)
  {
    char  acParam[1024], *pc1, *pc2;
    int   iLength, j;

    // Gets a local lower case copy
    iLength = strlen(argv[i]);
    for(j = 0, pc1 = acParam, pc2 = argv[i]; (j < iLength) && (j < 1024); pc1++, pc2++, j++)
    {
      *pc1 = ((*pc2 >= 'A') && (*pc2 <= 'Z')) ? *pc2 | 0x20 : *pc2;
    }
    *pc1 = '\0';

    // Is editor switch?
    if(!strcmp(acParam, szParamEditor))
    {
      // Updates editor status
      bEditor = true;
    }
  }

  // Editor mode?
  if(bEditor)
  {
    // Executes editor
    ScrollEd::GetInstance().Execute<G>(argc, argv);
  }
  else
  {
    // Executes game
    ScrollBase::GetInstance().Execute(argc, argv);
  }
#else // __NO_SCROLLED__

  // Executes game
  ScrollBase::GetInstance().Execute(argc, argv);

#endif // __NO_SCROLLED__
}

#ifdef __orxMSVC__

#include <windows.h>

template<class G>
void Scroll<G>::Execute()
{
  static const orxS32 szMaxArgs = 256;

  int   argc;
  char *argv[szMaxArgs];
  char *pcToken, *pcNextToken, *pcFirstDelimiters;
  LPSTR lpCmdLine;

  // Gets command line
  lpCmdLine = GetCommandLine();

  // Starts with a double quote?
  if(*orxString_SkipWhiteSpaces(lpCmdLine) == '"')
  {
    // Gets first delimiters
    pcFirstDelimiters = "\"";
  }
  else
  {
    // Gets first delimiters
    pcFirstDelimiters = " ";
  }

  // Process command line
  for(argc = 0, pcNextToken = orxNULL, pcToken = strtok_s(lpCmdLine, pcFirstDelimiters, &pcNextToken);
      pcToken && (argc < szMaxArgs);
      pcToken = strtok_s(orxNULL, " ", &pcNextToken))
  {
    argv[argc++] = pcToken;
  }

  // Calls main execute method
  Execute(argc, argv);
}

#endif // __orxMSVC__
