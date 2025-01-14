# Exit immediately if a command exits with a non-zero status.
set -e

ROOT=$PWD

# submodules
git submodule init
git submodule update

cd ros_ws/src/crazyswarm/externalDependencies/libmotioncapture/
git submodule init
git submodule update
cd $ROOT

# ros
cd ros_ws
catkin_make -DCMAKE_BUILD_TYPE=RelWithDebInfo
cd $ROOT
