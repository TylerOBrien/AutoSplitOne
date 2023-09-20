#include <Aso/App.hpp>
#include <Aso/Game.hpp>
#include <Aso/LiveSplit.hpp>
#include <Aso/Analyzers/Screen.hpp>
#include <Aso/Analyzers/EverDriveN8.hpp>
#include <Aso/IO/VideoCapture.hpp>

int main()
{
    aso::App app;
    aso::Game game;
    aso::VideoCapture capture;

    game.add<aso::ScreenAnalyzer>();
    game.add<aso::EverDriveN8Analyzer>();

    app.run();

    while (app.isAlive())
    {
        capture.refresh();
        game.updateFromCaptureFrame(capture.frame());

        while (aso::Event event = game.poll())
        {
            switch (event.type)
            {
            case aso::ScreenEvent::BLACK:
                aso::LiveSplit::split();
                break;
            case aso::EverDriveN8Event::MENU_OPEN:
                aso::LiveSplit::reset();
                break;
            }
        }

        app.sleep();
    }

    return 0;
}
