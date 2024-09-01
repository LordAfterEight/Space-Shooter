#include <SFML/Graphics.hpp>
using namespace sf;

Font fontAurebeshNormal;
Font fontDivlit;
Font fontNasalization;
Font fontPerfectDark;
Font fontRabidScience;
Font fontLDR;
Font fontLocust;
Font fontCorruptorClean;
Font fontCorruptorGlitch;
Font fontSprykski;
int loadFonts() {
    if (!fontAurebeshNormal.loadFromFile("fonts/aurebesh/Aurebesh.ttf")){return EXIT_FAILURE;}
    if (!fontDivlit.loadFromFile("fonts/divlit/divlit.ttf")){return EXIT_FAILURE;}
    if (!fontNasalization.loadFromFile("fonts/nasalization/nasalization.otf")){return EXIT_FAILURE;}
    if (!fontPerfectDark.loadFromFile("fonts/perfect-dark/pdark.ttf")){return EXIT_FAILURE;}
    if (!fontRabidScience.loadFromFile("fonts/rabid-science/RabidScience.ttf")){return EXIT_FAILURE;}
    if (!fontLDR.loadFromFile("fonts/2589-ldr/2589-LDR.ttf")){return EXIT_FAILURE;}
    if (!fontLocust.loadFromFile("fonts/cgf-locust-resistance/CGF Locust Resistance.ttf")){return EXIT_FAILURE;}
    if (!fontCorruptorClean.loadFromFile("fonts/corruptor/Corruptor-Clean-LDR.ttf")){return EXIT_FAILURE;}
    if (!fontCorruptorGlitch.loadFromFile("fonts/corruptor/Corruptor-LDR.ttf")){return EXIT_FAILURE;}
    if (!fontSprykski.loadFromFile("fonts/sprykski/Sprykski.otf")){return EXIT_FAILURE;}
    return 0;
}