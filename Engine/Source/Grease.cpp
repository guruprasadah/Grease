#include <Grease.h>

void Tick() {
    static Grease::Events::OnTickEvent OTE;
    Grease::Events::Brodcast(OTE);
}

int main() {
    Grease::Log("Engine Starting Up...");
    // Create basic things needed for gfx
    Grease::OS::Window Window = Grease::OS::Window::Create(1600, 900, "Grease Engine");
    Grease::GFX::Renderer Renderer = Grease::GFX::Renderer::Create(Window);
    // Just a lil status message
    Grease::Log("Engine initialization complete!");
    // Create main ticker
    Grease::Time::Ticker Ticker(10, Tick);

    //Grease::GFX::Mesh Mesh = Grease::GFX::Mesh::Create("ASSET://Doomguy.asset");

    while(Window.Open()) {
        Window.ProcessEvents();
        Renderer.NewFrame();
        Window.SwapBuffer();
    }
}