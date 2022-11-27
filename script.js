// preloader
setTimeout(function () {
    $('.preloader').fadeToggle();
}, 2000);

// navbar scripts
$(document).ready(function () {
    $(window).scroll(function () {
        if (this.scrollY > 20) {
            $('.nav-bar').addClass("scrolled");
        } else {
            $('.nav-bar').removeClass("scrolled");
        }

        if (this.scrollY > 500) {
            $('.scroll-up-btn').addClass("show");
        }
        else {
            $('.scroll-up-btn').removeClass("show");
        }
    });

    // slide-up script
    $('.scroll-up-btn').click(function () {
        $('html').animate({ scrollTop: 0 });
    });

    // Navbar Script
    $('.menu-btn').click(function () {
        $('.nav-bar .menu').toggleClass('active');
        $('.menu-btn i').toggleClass('active');
    });


    // animated text
    var typed = new Typed(".typing", {
        strings: ["detect climate change.", "fight global warming.", "decrease desertification."],
        typeSpeed: 100,
        backSpeed: 60,
        loop: true
    });

    // Carousel Script
    $('.carousel').owlCarousel({
        margin: 20,
        loop: true,
        autoplay: true,
        autoplayHoverPause: false,
        responsive: {
            0: {
                items: 1,
                nav: false
            },
            600: {
                items: 2,
                nav: false
            },
            1200: {
                items: 3,
                nav: false
            }
        }
    });
});