#ifndef CONFIG_HPP
#define CONFIG_HPP

constexpr bool isAmericanEnv() {
#ifdef USA
    return true;
#else
    return false;
#endif
}

#endif // CONFIG_HPP