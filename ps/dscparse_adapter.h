/** 
 * SPDX-FileCopyrightText: 2001 the KGhostView authors. See file AUTHORS.
 * 	
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef DSCPARSE_ADAPTER_H
#define DSCPARSE_ADAPTER_H

#include <iostream>
#include <map>
#include <memory>

#include <QSize>
#include <QString>

#include "dscparse.h"

#ifndef KDE_USE_FINAL
#undef min
#undef max
#endif

class KDSCBBOX
{
public:
    KDSCBBOX(); 
    KDSCBBOX( const KDSCBBOX& b );
    KDSCBBOX( int llx, int lly, int urx, int ury ); 
    KDSCBBOX( const CDSCBBOX& bbox ); 

    KDSCBBOX& operator = ( const KDSCBBOX& b );  
    
    bool operator == ( const KDSCBBOX& b ); 
    bool operator != ( const KDSCBBOX& b );
    
    int llx() const;
    int lly() const;
    int urx() const;
    int ury() const;

    int width()  const;
    int height() const;

    QSize size() const;

private:
    int _llx, _lly, _urx, _ury;
};

std::ostream& operator << ( std::ostream&, const KDSCBBOX& );


class KDSCError
{
public:
    enum Type
    {
	BBox             = CDSC_MESSAGE_BBOX,
	EarlyTrailer     = CDSC_MESSAGE_EARLY_TRAILER,
	EarlyEOF         = CDSC_MESSAGE_EARLY_EOF,
	PageInTrailer    = CDSC_MESSAGE_PAGE_IN_TRAILER,
	PageOrdinal      = CDSC_MESSAGE_PAGE_ORDINAL,
	PagesWrong       = CDSC_MESSAGE_PAGES_WRONG,
	EPSNoBBox        = CDSC_MESSAGE_EPS_NO_BBOX,
	EPSPages         = CDSC_MESSAGE_EPS_PAGES,
	NoMedia          = CDSC_MESSAGE_NO_MEDIA,
	AtEnd            = CDSC_MESSAGE_ATEND,
	DuplicateComment = CDSC_MESSAGE_DUP_COMMENT,
	DuplicateTrailer = CDSC_MESSAGE_DUP_TRAILER,
	BeginEnd         = CDSC_MESSAGE_BEGIN_END,
	BadSection       = CDSC_MESSAGE_BAD_SECTION,
	LongLine         = CDSC_MESSAGE_LONG_LINE,
	IncorrectUsage   = CDSC_MESSAGE_INCORRECT_USAGE
    };

    enum Severity
    {
	Information = CDSC_ERROR_INFORM,
	Warning     = CDSC_ERROR_WARN,
	Error       = CDSC_ERROR_ERROR
    };

    KDSCError( Type, Severity, const QByteArray& line, 
	       unsigned int lineNumber );
    
    Type         type()       const;
    Severity     severity()   const;
    QByteArray     line()       const;
    unsigned int lineNumber() const;
    
private:
    Type         _type;
    Severity     _severity;
    QByteArray     _line;
    unsigned int _lineNumber;
};


class KDSCErrorHandler
{
public:
    virtual ~KDSCErrorHandler() {}
    enum Response 
    { 
	Ok        = CDSC_RESPONSE_OK, 
	Cancel    = CDSC_RESPONSE_CANCEL,
	IgnoreAll = CDSC_RESPONSE_IGNORE_ALL
    };
    
    virtual Response error( const KDSCError& ) = 0;
};

class KDSCOkErrorHandler : public KDSCErrorHandler
{
    Response error( const KDSCError& ) override;
};

class KDSCCommentHandler
{
public:
    virtual ~KDSCCommentHandler() {}
    enum Name
    {
	// Header section
	PSAdobe               = CDSC_PSADOBE,
	BeginComments         = CDSC_BEGINCOMMENTS,
	EndComments           = CDSC_ENDCOMMENTS,
	Pages                 = CDSC_PAGES,
	Creator               = CDSC_CREATOR,
	CreationDate          = CDSC_CREATIONDATE,
	Title                 = CDSC_TITLE,
	For                   = CDSC_FOR,
	LanguageLevel         = CDSC_LANGUAGELEVEL,
	BoundingBox           = CDSC_BOUNDINGBOX,
	Orientation           = CDSC_ORIENTATION,
	PageOrder             = CDSC_PAGEORDER,
	DocumentMedia         = CDSC_DOCUMENTMEDIA,
	DocumentPaperSizes    = CDSC_DOCUMENTPAPERSIZES,
	DocumentPaperForms    = CDSC_DOCUMENTPAPERFORMS,
	DocumentPaperColors   = CDSC_DOCUMENTPAPERCOLORS,
	DocumentPaperWeights  = CDSC_DOCUMENTPAPERWEIGHTS,
	DocumentData          = CDSC_DOCUMENTDATA,
	Requirements          = CDSC_REQUIREMENTS,
	DocumentNeededFonts   = CDSC_DOCUMENTNEEDEDFONTS,
	DocumentSuppliedFonts = CDSC_DOCUMENTSUPPLIEDFONTS,
	HiResBoundingBox      = CDSC_HIRESBOUNDINGBOX,
	CropBox               = CDSC_CROPBOX,
	
	// Preview section
	BeginPreview          = CDSC_BEGINPREVIEW,
	EndPreview            = CDSC_ENDPREVIEW,

	// Defaults section
	BeginDefaults         = CDSC_BEGINDEFAULTS,
	EndDefaults           = CDSC_ENDDEFAULTS,
	// also %%PageMedia, %%PageOrientation, %%PageBoundingBox

	// Prolog section 
	BeginProlog           = CDSC_BEGINPROLOG,
	EndProlog             = CDSC_ENDPROLOG,
	BeginFont             = CDSC_BEGINFONT,
	EndFont               = CDSC_ENDFONT,
	BeginFeature          = CDSC_BEGINFEATURE,
	EndFeature            = CDSC_ENDFEATURE,
	BeginResource         = CDSC_BEGINRESOURCE,
	EndResource           = CDSC_ENDRESOURCE,
	BeginProcset          = CDSC_BEGINPROCSET,
	EndProcset            = CDSC_ENDPROCSET,

	// Setup section
	BeginSetup            = CDSC_BEGINSETUP,
	EndSetup              = CDSC_ENDSETUP,
	Feature               = CDSC_FEATURE,
	PaperColor            = CDSC_PAPERCOLOR,
	PaperForm             = CDSC_PAPERFORM,
	PaperWeight           = CDSC_PAPERWEIGHT,
	PaperSize             = CDSC_PAPERSIZE,
	// also %%Begin/EndFeature, %%Begin/EndResource

	// Page section
	Page                  = CDSC_PAGE,
	PageTrailer           = CDSC_PAGETRAILER,
	BeginPageSetup        = CDSC_BEGINPAGESETUP,
	EndPageSetup          = CDSC_ENDPAGESETUP,
	PageMedia             = CDSC_PAGEMEDIA,
	// also %%PaperColor, %%PaperForm, %%PaperWeight, %%PaperSize
	PageOrientation       = CDSC_PAGEORIENTATION,
	PageBoundingBox       = CDSC_PAGEBOUNDINGBOX,
	// also %%Begin/EndFont, %%Begin/EndFeature 
	// also %%Begin/EndResource, %%Begin/EndProcSet 
	IncludeFont           = CDSC_INCLUDEFONT,
	ViewingOrientation    = CDSC_VIEWINGORIENTATION,

	// Trailer section
	Trailer               = CDSC_TRAILER,
	// also %%Pages, %%BoundingBox, %%Orientation, %%PageOrder, 
	// %%DocumentMedia
	// %%Page is recognised as an error
	// also %%DocumentNeededFonts, %%DocumentSuppliedFonts

	// End of File */
	Eof                    = CDSC_EOF
    };
	
    virtual void comment( Name name ) { std::cout << name << std::endl; }
};

class KDSCScanHandler;
class KDSC
{
public:
    KDSC();
    ~KDSC();

    /*--- Adapter for CDSC ------------------------------------------------*/
    QString dsc_version() const;
    
    bool dsc()   const;
    bool ctrld() const;
    bool pjl()   const;
    bool epsf()  const;
    bool pdf()   const;
    
    unsigned int preview()        const;
    unsigned int language_level() const;
    unsigned int document_data()  const;

    unsigned long begincomments() const;
    unsigned long endcomments()   const;
    unsigned long beginpreview()  const;
    unsigned long endpreview()    const;
    unsigned long begindefaults() const;
    unsigned long enddefaults()   const;
    unsigned long beginprolog()   const;
    unsigned long endprolog()     const;
    unsigned long beginsetup()    const;
    unsigned long endsetup()      const;
    unsigned long begintrailer()  const;
    unsigned long endtrailer()    const;

    CDSCPAGE* page() const;

    unsigned int page_count()       const;
    unsigned int page_pages()       const;
    unsigned int page_order()       const;
    unsigned int page_orientation() const;

    CDSCCTM* viewing_orientation() const;
    
    unsigned int media_count()    const;
    CDSCMEDIA** media()           const;
    const CDSCMEDIA* page_media() const;

    std::unique_ptr<KDSCBBOX> bbox()      const;
    std::unique_ptr<KDSCBBOX> page_bbox() const;

    // CDSCDOSEPS *doseps;

    QString dsc_title()   const;
    QString dsc_creator() const;
    QString dsc_date()    const;
    QString dsc_for()     const;

    // unsigned int max_error
   
    bool scanData( char*, unsigned int );

    /**
     * Tidy up from incorrect DSC comments.
     */
    int fixup();
    
    KDSCErrorHandler* errorHandler() const;
    void setErrorHandler( KDSCErrorHandler* );
    
    KDSCCommentHandler* commentHandler() const;
    void setCommentHandler( KDSCCommentHandler* );
    
    /*--- Extra methods for convenience -----------------------------------*/
    bool isStructured() const;

    /*--- Temporary -------------------------------------------------------*/
    CDSC* cdsc() const;

protected:
    static int errorFunction( void* caller_data, CDSC* dsc, 
                              unsigned int explanation, 
                              const char* line, unsigned int line_len );
    
private:
    CDSC*               _cdsc;
    KDSCErrorHandler*   _errorHandler;
    KDSCCommentHandler* _commentHandler;
    KDSCScanHandler*    _scanHandler;
};

class KDSCScanHandler
{
public:
    virtual ~KDSCScanHandler() {}
    KDSCScanHandler( CDSC* cdsc ) : _cdsc( cdsc ) {}
    
    virtual bool scanData( char* buf, unsigned int count )
    {
	return ( dsc_scan_data( _cdsc, buf, count ) >= 0 );
    }
    
protected:
    CDSC* _cdsc;
};

class KDSCScanHandlerByLine : public KDSCScanHandler
{
public:
    KDSCScanHandlerByLine( CDSC* cdsc, KDSCCommentHandler* commentHandler ) : 
	KDSCScanHandler( cdsc ),
	_commentHandler( commentHandler ) 
    {}
    
    bool scanData( char* buf, unsigned int count ) override;

protected:
    KDSCCommentHandler* _commentHandler;
};

#endif

// vim:sw=4:sts=4:ts=8:noet
