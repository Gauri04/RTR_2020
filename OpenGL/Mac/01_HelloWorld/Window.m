#import <Foundation/Foundation.h> 
#import <Cocoa/Cocoa.h> // analogous to windows.h or xlib.h

@interface AppDelegate:NSObject <NSApplicationDelegate, NSWindowDelegate>
@end

int main (int argc, const char * argv[])
{
  // code
  NSAutoreleasePool *grpool = [[NSAutoreleasePool alloc] init]; // allocate memory and initialize
  NSApp = [NSApplication sharedApplication];                    // NSApp similar to HINSTANCE, get nsapp //by calling sharedApplication method
  [NSApp setDelegate : [[AppDelegate alloc] init]];     // setDelegate calls applicationDidFinishLaunching() which is similar to WM_CREATE
  
  // when application terminates, it calls NSApp's applicationWillTerminate() method
  
  // message loop
  [NSApp run];
  [grpool release];
  return 0;
}

@interface MyView:NSView            // declaration of MyView, MyView extends NSView
@end

@implementation AppDelegate
{
    @private NSWindow *grwindow;
    MyView *grview;
}

-(void)applicationDidFinishLaunching:(NSNotification *) aNotification
{
    // code
    NSRect win_rect = NSMakeRect(0.0, 0.0, 800.0, 600.0);   // NSRect is internally CGRect from CoreGraphics(C lang. library) and its a struct so no alloc
    grwindow = [[NSWindow alloc] initWithContentRect:win_rect 
                                styleMask:NSWindowStyleMaskTitled |
                                    NSWindowStyleMaskClosable |
                                    NSWindowStyleMaskMiniaturizable |
                                    NSWindowStyleMaskResizable 
                                backing:NSBackingStoreBuffered 
                                defer:NO];
    
    [grwindow setTitle:@"GR Mac Window"];
    [grwindow center];
    
    // create view
    grview = [[MyView alloc]initWithFrame:win_rect];
    // apply view
    [grwindow setContentView:grview];
    [grwindow setDelegate:self];
    [grwindow makeKeyAndOrderFront:self];         // same as setForegroundWindow, keep the window to front and set keyboard focus to my window
    
}

-(void)applicationWillTerminate:(NSNotification *) aNotification
{
    // code
}

-(void)windowWillClose:(NSNotification *) aNotification
{
    // code
    [NSApp terminate:self];
}

-(void)dealloc
{
    // code
    [grview release];
    [grwindow release];
    [super dealloc];
}
@end

@implementation MyView
{
    @private NSString *centralText;
}

-(id)initWithFrame:(NSRect) frame
{
    // code
    self = [super initWithFrame:frame];
    if(self)
    {
        centralText = @"Hello World..!!";
        
    }
    return self;
}

-(void)drawRect:(NSRect) dirtyRect                          // simiar to WM_PAINT
{
    NSColor *backgroundColor = [NSColor blackColor];
    [backgroundColor set];
    NSRectFill(dirtyRect);
    
    // set text and display it in center of window
    NSDictionary *dictionaryForTextAttribs = [NSDictionary dictionaryWithObjectsAndKeys:
        [NSFont fontWithName:@"Helvetica" size:32], NSFontAttributeName,
        [NSColor greenColor], NSForegroundColoAttributeName, nil];
        
    NSSize textSize = [centralText sizeWithAttributes:dictionaryForTextAttribs];
    
    NSPoint point;
    point.x = (dirtyRect.size.width / 2) - (textSize.width / 2);    // horizontal center for text
    point.y = (dirtyRect.size.height / 2) - (textSize.height / 2) + 12; // normally titlebar is of size 12 hence adjust according to titlebar
    
    [centralText drawAtPoint:point withAttributes:dictionaryForTextAttribs];
}

-(BOOL)acceptsFirstResponder
{
    [[self window]makeFirstResponder];
    return YES;
}

-(void) keyDown:(NSEvent *) theEvent
{
    int key = [[theEvent characters]characterAtIndex:0];
    switch(key)
    {
        case 27:                    // escape key
            [self release];
            [NSApp terminate:self];
            break;
            
        case 'F':
        case 'f':
            [[self window]toggleFullScreen:self];
            break;
    }
}

-(void) mouseDown:(NSEvent *) theEvent
{
    centralText = @"Left mouse button is clicked";
    [self setNeedsDisplay:YES];
}

-(void) rightMouseDown(NSEvent *) theEvent
{
    // code
    centralText = @"Right mouse button is clicked";
    [self setNeedsDisplay:YES];
}

-(void) otherMouseDown(NSEvent *) theEvent
{
     centralText = @"Middle mouse button is clicked";
    [self setNeedsDisplay:YES];
}

-(void) dealloc
{
    [super dealloc];
}
@end











