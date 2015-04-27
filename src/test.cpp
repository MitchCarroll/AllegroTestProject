/* C. Mitch Carroll
   This is a simple test program for Allegro5 and CMake.
   this file is part of a test project which can be used as boilerplate
   for making new CMake/Allegro5 projects

   I have yet to figure out some more advanced topics, like Android 
   deployment.
   As of right now this works on Linux for sure :-)
*/

#include <allegro5/allegro.h> //must be included by any allegro program
#include <allegro5/allegro_image.h> //allows us to load images and such
#include <iostream> //just for my error message
//incidentally, this should really be done with an allegro messagebox
using namespace std; //because I really hate typing std:: before stuff.

int main(int argc, char **argv)
//Allegro requires your main function to have this signature
{
  al_init(); //initialize allegro itself
  al_set_new_display_flags(ALLEGRO_WINDOWED);
  //do this stuff before creating
                                              //the new window
  ALLEGRO_DISPLAY *screen=al_create_display(800,600); //800X600 window
  al_set_window_title(screen,"Test"); //sets the text of the titlebar
  al_set_target_backbuffer(screen); //sets the destination for drawing

  al_init_image_addon(); //initialize the image libraries
  al_install_keyboard(); //enable keyboard support

  ALLEGRO_EVENT_QUEUE *event_queue = NULL; //this is where our events go
  event_queue = al_create_event_queue(); //initialize it...
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  //now it is set to record keyboard events
  
  ALLEGRO_BITMAP *my_pic = NULL; //allocate memory for an image
  my_pic = al_load_bitmap(DATADIR "test.png"); //load the image
  //NOTE: DATADIR is a constant which is set by our CMake setup
  //at compile time
  //it is a string that is tacked onto the front of the filename so the
  //program
  //can find it (after installing)
  //e.g.: "/usr/local/share/AllegroTestProgram/data/"
  //this way, instead of typing someting like load("myFile.dat") you
  //can do:
  //load(DATADIR "myFile.dat")
  al_clear_to_color(al_map_rgb_f(.5,.5,.5));
  if(!my_pic) //if the file doesn't load right, or isn't found
    cout << DATADIR << "test.png" << " DIDN'T LOAD!" << endl;
  //print an error
  else {
    al_draw_bitmap(my_pic, 0, 0, 0); //draw the image to the window
    al_draw_scaled_rotated_bitmap(my_pic,
				  256,256,
				  600,200,
				  0.5, 1.5,
				  45,
				  0);
  }
  
  al_flip_display();
  //flip the backbuffer to the screen so we can see it

  bool done=false; //this just stores whether we want to quit yet or not
  while(!done) 
    {
      ALLEGRO_EVENT ev; //this represents a single event
      al_wait_for_event(event_queue, &ev);
      //when an event is captured, put it in ev
      
      if(ev.type == ALLEGRO_EVENT_KEY_DOWN) //if it's a keypress...
	{
	  switch(ev.keyboard.keycode)
	    {
	    case ALLEGRO_KEY_ESCAPE: //and it's the ESC key...
	      done = true; //then we are done
	      break;
	    default:
	      //it's good practice to always define a default case
	      break;
	    }
	}
    }

  //before quitting, free up all our resources so we don't leak RAM
  al_destroy_bitmap(my_pic);
  al_destroy_event_queue(event_queue);
  al_destroy_display(screen);  
  return 0;
}
//you no longer need END_OF_MAIN() or anything with allegro5
