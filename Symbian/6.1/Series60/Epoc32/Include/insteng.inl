// INSTENG.INL
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Installer engine inline methods
//

inline TBool CInstallEngine::IsRecursive() const { return iParentInstaller!=NULL; }
inline void CInstallEngine::SetParentInstaller(CInstaller* parent) { iParentInstaller=parent; }
inline CInstaller* CInstallEngine::ParentInstaller() { return iParentInstaller; }

