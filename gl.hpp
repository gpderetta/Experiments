#ifndef EB_GL_HPP
#define EB_GL_HPP
#include <GL/gl.h>
#include <GL/glu.h>

#include "color.hpp"
namespace eb { namespace gl {

        struct graphic_context {
    
            /* function to release/destroy our resources and restoring the old desktop */
            ~graphic_context() {
                /* Clean up our textures */
                glDeleteTextures( 1, &texture[0] );
        
                /* clean up the window */
                SDL_Quit( );
        
            }


            /* function to reset our viewport after a window resize */
            void resize_window( int width, int height )
            {
                /* Protect against a divide by zero */
                if ( height == 0 )
                    height = 1;
                /* Height / width ration */
                GLfloat ratio =
                    ( GLfloat )width /
                    ( GLfloat )height;
        
                /* Setup our viewport. */
                glViewport( 0, 0, ( GLint )width, ( GLint )height );
        
                /* change to the projection matrix and set our viewing volume. */
                glMatrixMode( GL_PROJECTION );
                glLoadIdentity( );
        
                /* Set our perspective */
                gluPerspective( 45.0f, ratio, 0.1f, 200.0f );
        
                /* Make sure we're chaning the model view and not the projection */
                glMatrixMode( GL_MODELVIEW );
        
                /* Reset The View */
                glLoadIdentity( );
            }

            /* function to load in bitmap as a GL texture */
            void load_textures() {
                SDL_Surface *texture_image[1] = {
                    SDL_LoadBMP( "data/particle.bmp" )  };
                if (texture_image[0])
                    abort();

                glGenTextures( 1, &m_texture[0] );
                glBindTexture( GL_TEXTURE_2D, m_texture[0] );
                glTexImage2D( GL_TEXTURE_2D, 0, 3,
                              texture_image[0]->w,
                              texture_image[0]->h, 0, GL_BGR,
                              GL_UNSIGNED_BYTE,
                              texture_image[0]->pixels );

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                                GL_LINEAR );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                                GL_LINEAR );
        
                SDL_FreeSurface(texture_image[0]);

        
            }

            void graphic_context(){
                load_texture();
            
                // enable smooth shading 
                glShadeModel( GL_SMOOTH );
                // set the background black 
                glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
                // depth buffer setup 
                glClearDepth( 1.0f );
                glDisable( GL_DEPTH_TEST );
                // enable blending 
                glEnable( GL_BLEND );
                glBlendFunc( GL_SRC_ALPHA, GL_ONE );
                glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
                glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
                glEnable( GL_TEXTURE_2D );
                glBindTexture( GL_TEXTURE_2D, texture[0] );
            }


            void reset() {
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );         glLoadIdentity( );
            }

            void swap_buffers() {
                /* Draw it to the screen */
                SDL_GL_SwapBuffers( );
            }
        
         private:
            GLuint m_texture[1];
            
        };

        // draw a square centered around p using the
        // currently bound texture.
        void draw_dot(const position p, 
                      const color c = color(1,1,1),
                      const float alpha = 1.0f,
                      const float radius = 0.5f) {
            const float x = p.x();
            const float y = p.y();
            float z = 0;
            glColor4f( color.r,
                       color.g,
                       color.b,
                       alpha );
        
            /* Build Quad From A Triangle Strip */
            glBegin( GL_TRIANGLE_STRIP );
            /* Top Right */
            glTexCoord2d( 1, 1 );
            glVertex3f( x + radius, y + radius, z );
            /* Top Left */
            glTexCoord2d( 0, 1 );
            glVertex3f( x - radius, y + radius, z );
            /* Bottom Right */
            glTexCoord2d( 1, 0 );
            glVertex3f( x + radius, y - radius, z );
                /* Bottom Left */
            glTexCoord2d( 0, 0 );
            glVertex3f( x - radius, y - radius, z );
            glEnd( );
        }
        
        template<typename T>
        draw_scene (T const& x) {
            gl::reset();
            draw(x);
            gl::swap_buffers();
        };
    }
}
#endif 

    
