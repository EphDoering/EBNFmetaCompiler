/*
 * EBNFmetaNames.h
 *
 *  Created on: Mar 18, 2016
 *      Author: frederick.doering
 */
#ifdef EBNFMETANAMES_VAR //if trying to set the string array

#ifndef EBNFMETANAMES_H_VAR  //make sure we only initialize it once
#define EBNFMETANAMES_H_VAR

#define EBNFMETANAMESstartList(name) EBNFMETANAMES_VAR={
#define EBNFMETANAMESENUM_TEXT(thing) #thing
#define EBNFMETANAMESENDLIST(name) };


#define EBNFMETANAMES_DO_IT  //actually do something
#endif

#else  //declaring the enum

#ifndef EBNFMETANAMES_H_ENUM //make sure we only declare the enum once
#define EBNFMETANAMES_H_ENUM

#define EBNFMETANAMESstartList(name) enum name {
#define EBNFMETANAMESENUM_TEXT(thing) thing
#define EBNFMETANAMESENDLIST(name) , NUM_##name };

#define EBNFMETANAMES_DO_IT //actually do something
#endif

#endif


#ifdef EBNFMETANAMES_DO_IT

namespace metaParser {


EBNFMETANAMESstartList(EBNFmID)
	EBNFMETANAMESENUM_TEXT(SYNTAX),
	EBNFMETANAMESENUM_TEXT(SYNTAXRULE),
	EBNFMETANAMESENUM_TEXT(DEFINITIONSLIST),
	EBNFMETANAMESENUM_TEXT(SINGLEDEFINITION),
	EBNFMETANAMESENUM_TEXT(TERM),
	EBNFMETANAMESENUM_TEXT(EXCEPTION),
	EBNFMETANAMESENUM_TEXT(FACTOR),
	EBNFMETANAMESENUM_TEXT(PRIMARY),
	EBNFMETANAMESENUM_TEXT(EMPTY),
	EBNFMETANAMESENUM_TEXT(OPTIONALSEQUENCE),
	EBNFMETANAMESENUM_TEXT(REPEATEDSEQUENCE),
	EBNFMETANAMESENUM_TEXT(GROUPEDSEQUENCE),
	EBNFMETANAMESENUM_TEXT(TERMINAL),
	EBNFMETANAMESENUM_TEXT(METAIDENTIFIER),
	EBNFMETANAMESENUM_TEXT(INTEGER),
	EBNFMETANAMESENUM_TEXT(SPECIALSEQUENCE)
EBNFMETANAMESENDLIST(EBNFmID)



} //end namespace metaParser

#undef EBNFMETANAMESstartList
#undef EBNFMETANAMESENUM_TEXT
#undef EBNFMETANAMESENDLIST
#undef EBNFMETANAMES_DO_IT
#endif /* EBNFMETANAMES_H_ */

