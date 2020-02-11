# A Minimum Example of Connecting to Interactive Broker API in CPP

Because the official example in the [downable API](https://interactivebrokers.github.io/#) is full of nonsense...

This cuts a lot of unnecessary codes in the official TestClient and focus on what's the minimum amoumt of code needed (with missing functionalities).

## Prerequisite

-   Enable API access in TWS or use IB Gateway as [offical doc suggested](https://interactivebrokers.github.io/tws-api/initial_setup.html) and keep TWS / IB Gateway on

-   Install [bazel](https://docs.bazel.build/install.html)

-   Copy the C++ API source code into `//third_party/ibapi`

    - Make sure everything can build:
    ```shell
    $ bazel build third_party/ibapi
    ```

-   Build and run the program

    ```shell
    $ bazel run client:main
    ```
