/////////////////////////////////////////////////////////////////////////////
// Name:        slider.cpp
// Purpose:     wxSlider
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// RCS-ID:      $Id$
// Copyright:   (c) Stefan Csomor
// Licence:       wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "wxprec.h"

#if wxUSE_SLIDER

#include "wx/slider.h"
#include "wx/osx/private.h"

wxWidgetImplType* wxWidgetImpl::CreateSlider( wxWindowMac* wxpeer,
                                    wxWindowMac* parent,
                                    wxWindowID WXUNUSED(id),
                                    wxInt32 value,
                                    wxInt32 minimum,
                                    wxInt32 maximum,
                                    const wxPoint& pos,
                                    const wxSize& size,
                                    long style,
                                    long WXUNUSED(extraStyle))
{
    Rect bounds = wxMacGetBoundsForControl( wxpeer, pos, size );
    int tickMarks = 0;
    if ( style & wxSL_AUTOTICKS )
        tickMarks = (maximum - minimum) + 1; // +1 for the 0 value

    // keep the number of tickmarks from becoming unwieldly, therefore below it is ok to cast
    // it to a UInt16
    while (tickMarks > 20)
        tickMarks /= 5;


    wxMacControl* peer = new wxMacControl( wxpeer );
    OSStatus err = CreateSliderControl(
        MAC_WXHWND(parent->MacGetTopLevelWindowRef()), &bounds,
        value, minimum, maximum,
        kControlSliderPointsDownOrRight,
        (UInt16) tickMarks, true /* liveTracking */,
        GetwxMacLiveScrollbarActionProc(),
        peer->GetControlRefAddr() );
    verify_noerr( err );

    return peer;
}

#endif // wxUSE_SLIDER
