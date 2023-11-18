#ifndef DRAW_ROUTINES_H_
#define DRAW_ROUTINES_H_

#ifdef GRAPHICS_NS //namespace only functions

        //these includes are also took by window.c FIXME
        #include "../../level/level.h" //for room definition
        #include "../structures/text.h" //for text definition
        #include "window.h"


        void _draw_room( struct Window*, struct Room* );

        void _draw_text( struct Window*, struct Text* );

#endif

#endif //DRAW_ROUTINES_H_
