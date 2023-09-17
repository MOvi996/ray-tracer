#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>

#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <cmath>

#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/directional.h>

#include <rt/materials/lambertian.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/dielectric.h>
#include <rt/materials/conductor.h>
#include <rt/materials/fuzzyconductor.h>
#include <rt/materials/phong.h>
#include <rt/materials/combine.h>

#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/checkerboard.h>
#include <rt/textures/perlin.h>

#include <rt/solids/quad.h>
#include <rt/solids/triangle.h>
#include <rt/solids/sphere.h>
#include <rt/solids/aabox.h>
#include <rt/solids/disc.h>
#include <rt/solids/infiniteSolid.h>

#include <rt/integrators/raytrace.h>
#include <rt/integrators/recraytrace.h>
#include <rt/integrators/casting.h>

#include <rt/groups/group.h>
#include <rt/groups/simplegroup.h>
#include <rt/groups/bvh.h>
#include <rt/loaders/obj.h>
#include <rt/coordmappers/plane.h>
#include <rt/coordmappers/cylindrical.h>
#include <rt/coordmappers/spherical.h>
#include <rt/coordmappers/tmapper.h>
#include <rt/coordmappers/environment.h>

#include <rt/primmod/instance.h>



using namespace rt;


void create_scene(){
    
    BVH* scene = new BVH();

    
    Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    Texture* whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    Texture* bluetex = new ConstantTexture(RGBColor(0.021f, 0.047f, 0.8f));
    Texture* browntex = new ConstantTexture(RGBColor(0.43f, 0.15f, 0.055f));
    Texture* greytex = new ConstantTexture(RGBColor::rep(0.4f));
    Texture* purpletex = new ConstantTexture(RGBColor(0.921f, 0.804f, 1.f));
    Texture* orangetex = new ConstantTexture(RGBColor(0.985f, 0.639f, 0.102f));
    

    PerlinTexture* table_tex_noise = new PerlinTexture(RGBColor(0.43f, 0.15f, 0.055f)*1.4f, RGBColor::rep(0.f));
    table_tex_noise->addOctave(0.7f, 2.f);
    table_tex_noise->addOctave(0.8f, 5.f);
    table_tex_noise->addOctave(0.55f, 12.f);
    table_tex_noise->addOctave(0.6f, 20.0f);
    table_tex_noise->addOctave(0.4f, 80.0f);

    PerlinTexture* cat_tex_noise = new PerlinTexture(RGBColor::rep(0.7f), RGBColor::rep(0.1f));
    cat_tex_noise->addOctave(0.7f, 2.f);
    cat_tex_noise->addOctave(0.8f, 5.f);
    cat_tex_noise->addOctave(0.55f, 12.f);
    cat_tex_noise->addOctave(0.6f, 20.0f);
    cat_tex_noise->addOctave(0.4f, 80.0f);


    Material* white = new LambertianMaterial(blacktex, whitetex);
    Material* blue = new LambertianMaterial(blacktex, bluetex);
    Material* brown = new LambertianMaterial(blacktex, browntex);
    Material* metal_mat = new FuzzyConductorMaterial(6.f, 3.433f, pi / 10.f);
    Material* phong_mat = new PhongMaterial(greytex, 10.f);
    Material* dielectric_mat = new DielectricMaterial(3.f);
    
    Point source(-0.5f,-3.f, -0.5f);
    
    /////////////
    // Objects //
    /////////////


    // table 
    BVH * table = new BVH();
    loadOBJ(table, "../rc_models/", "table.obj", );
    ImageTexture* table_tex = new ImageTexture("../rc_models/table_col.png",ImageTexture::REPEAT, ImageTexture::BILINEAR);
    //CombineMaterial* table_mat = new CombineMaterial();
    //LambertianMaterial* base_mat = new LambertianMaterial(blacktex, table_tex_noise);
    Material* top_mat = new LambertianMaterial(blacktex, table_tex);
    //table_mat->add(base_mat,0.3);
    //table_mat->add(top_mat,.9);
    table->setMaterial(top_mat);
    table->rebuildIndex();
    scene->add(table);

    // siamese cat
    BVH * siamese_cat = new BVH();
    loadOBJ(siamese_cat, "../rc_models/", "siamese_cat.obj");
    //CombineMaterial* siamese_cat_mat = new CombineMaterial();    
    Material* siamese_cat_fur = new LambertianMaterial(blacktex, new ImageTexture("../rc_models/siamese_cat_fur.png"));
    //LambertianMaterial* cat_skin = new LambertianMaterial(blacktex, cat_tex_noise);
    //siamese_cat_mat->add(cat_skin,0.05);
    //siamese_cat_mat->add(siamese_cat_fur,.9);
    //siamese_cat_mat->add(new PhongMaterial(orangetex, 0.3f), 0.1);
    siamese_cat->setMaterial(siamese_cat_fur);
    siamese_cat->rebuildIndex();
    scene->add(siamese_cat);

    // gray cat
    BVH * gray_cat = new BVH();
    loadOBJ(gray_cat, "../rc_models/", "gray_cat.obj");
    //CombineMaterial* gray_cat_mat = new CombineMaterial();
    Material* gray_cat_fur = new LambertianMaterial(blacktex, new ImageTexture("../rc_models/GreyTabb.png"));
    //gray_cat_mat->add(gray_cat_fur, 0.9);
    //gray_cat_mat->add(cat_skin, 0.05);
    //gray_cat_mat->add(new PhongMaterial(greytex, 0.3f), 0.1);
    gray_cat->setMaterial(gray_cat_fur);
    gray_cat->rebuildIndex();
    scene->add(gray_cat);


    // carpet
    BVH * floor = new BVH();
    loadOBJ(floor, "../rc_models/", "carpet.obj");
    ImageTexture* floor_tex = new ImageTexture("../rc_models/carpet.png",ImageTexture::REPEAT, ImageTexture::BILINEAR);
    LambertianMaterial* floor_mat = new LambertianMaterial(blacktex, floor_tex);
    floor->setMaterial(floor_mat);
    floor->rebuildIndex();
    scene->add(floor);


    // Walls 

    TriangleMapper* bottomleft = new TriangleMapper(Point(0,0,0), Point(0,1,0),Point(1,0,0));
    TriangleMapper* topright = new TriangleMapper(Point(1,1,0), Point(1,0,0),Point(0,1,0));

    ImageTexture* wall_tex = new ImageTexture("../rc_models/gray-wall.png",ImageTexture::REPEAT, ImageTexture::BILINEAR);
    LambertianMaterial* wall_mat = new LambertianMaterial(blacktex, wall_tex);
    

    // back wall
    BVH * back_wall = new BVH();
    loadOBJ(back_wall, "../rc_models/", "back_wall.obj");
    back_wall->setMaterial(wall_mat);
    back_wall->rebuildIndex();

    Instance* bw_ins = new Instance(back_wall);
    BBox bw_bounds = bw_ins->getBounds();
    
    Triangle* bwall_l = new Triangle(bw_bounds.min, Point(bw_bounds.min.x, bw_bounds.min.y, bw_bounds.max.z), Point(bw_bounds.max.x, bw_bounds.min.y, bw_bounds.min.z), bottomleft, wall_mat);
    Triangle* bwall_r = new Triangle(Point(bw_bounds.max.x, bw_bounds.min.y, bw_bounds.max.z), Point(bw_bounds.max.x, bw_bounds.min.y, bw_bounds.min.z), Point(bw_bounds.min.x, bw_bounds.min.y, bw_bounds.max.z), topright, wall_mat);
    
    scene->add(bwall_l);
    scene->add(bwall_r);

    // right wall
    BVH * r_wall = new BVH();
    loadOBJ(r_wall, "../rc_models/", "right_wall.obj");
    r_wall->setMaterial(wall_mat);
    r_wall->rebuildIndex();
    

    Instance* rw_ins = new Instance(r_wall);
    rw_ins->translate(Vector(-1,0,0));
    
    BBox rw_bounds = rw_ins->getBounds();
    
    Triangle* rwall_l = new Triangle(Point(rw_bounds.max.x+1.f, rw_bounds.min.y, rw_bounds.min.z),
                                     Point(rw_bounds.max.x+1.f, rw_bounds.min.y, rw_bounds.max.z), 
                                     Point(rw_bounds.max.x+1.f, rw_bounds.max.y, rw_bounds.min.z), bottomleft, wall_mat);
    Triangle* rwall_r = new Triangle(Point(rw_bounds.max.x+1.f, rw_bounds.max.y, rw_bounds.max.z), 
                                     Point(rw_bounds.max.x+1.f, rw_bounds.max.y, rw_bounds.min.z),
                                     Point(rw_bounds.max.x+1.f, rw_bounds.min.y, rw_bounds.max.z), 
                                    topright, wall_mat);
    
    scene->add(rwall_l);
    scene->add(rwall_r);

    // ceiling
    BVH * ceiling = new BVH();
    loadOBJ(ceiling, "../rc_models/", "ceiling.obj");
    ImageTexture* ceiling_tex = new ImageTexture("../rc_models/ceiling.png",ImageTexture::REPEAT, ImageTexture::BILINEAR);
    LambertianMaterial* ceiling_mat = new LambertianMaterial(blacktex, ceiling_tex);
    ceiling->setMaterial(ceiling_mat);
    ceiling->rebuildIndex();
    scene->add(ceiling);

    //catbowl
    BVH * catbowl = new BVH();
    loadOBJ(catbowl, "../rc_models/", "catbowl.obj");
    CombineMaterial* catbowl_mat = new CombineMaterial();
    catbowl_mat->add(blue,1.f);
    catbowl_mat->add(metal_mat, 0.7f);
    catbowl->setMaterial(catbowl_mat);
    catbowl->rebuildIndex();
    scene->add(catbowl);

    // food
    BVH * food = new BVH();
    loadOBJ(food, "../rc_models/", "food.obj");
    food->setMaterial(brown);
    food->rebuildIndex();
    scene->add(food);

    // scratching pole
    BVH * pole = new BVH();
    loadOBJ(pole, "../rc_models/", "scratching_Pole.obj");
    CombineMaterial* pole_mat = new CombineMaterial();
    pole_mat->add(ceiling_mat,1.f);
    pole_mat->add(phong_mat, 1.f);
    pole->setMaterial(pole_mat);
    pole->rebuildIndex();
    scene->add(pole);

    // scratch threads
    BVH * scratch_threads = new BVH();
    loadOBJ(scratch_threads, "../rc_models/", "scratch_threads.obj");
    CombineMaterial* threads_mat = new CombineMaterial();
    threads_mat->add(pole_mat, 1.f);
    threads_mat->add(white, 0.4f);
    scratch_threads->setMaterial(threads_mat);
    
    scratch_threads->rebuildIndex();
    scene->add(scratch_threads);


    // window
    BVH* window = new BVH();
    loadOBJ(window, "../rc_models/", "window.obj");
    ImageTexture* window_tex = new ImageTexture("../rc_models/ceiling.png",ImageTexture::REPEAT, ImageTexture::BILINEAR);
    CombineMaterial* window_mat = new CombineMaterial();
    window_mat->add(new LambertianMaterial(blacktex, window_tex),0.3);
    window_mat->add(white, 0.7);
    window->setMaterial(window_mat);
    window->rebuildIndex();
    scene->add(window);

    
    // pigeon
    BVH* pigeon = new BVH();
    loadOBJ(pigeon, "../rc_models/", "pigeon.obj");
    ImageTexture* pigeon_tex = new ImageTexture("../rc_models/pigeon.png",ImageTexture::REPEAT, ImageTexture::BILINEAR);
    //CombineMaterial* pigeon_mat = new CombineMaterial();
    Material* pigeon_fur = new LambertianMaterial(blacktex, pigeon_tex)
    //pigeon_mat->add(new LambertianMaterial(blacktex, pigeon_tex),1.f);
    //pigeon_mat->add(new PhongMaterial(purpletex,3.f), 0.5);
    pigeon->setMaterial(pigeon_fur);
    pigeon->rebuildIndex();
    scene->add(pigeon);


    // view 
    ImageTexture* viewtex = new ImageTexture("../rc_models/scenery-2.png", ImageTexture::REPEAT, ImageTexture::BILINEAR);
    LambertianMaterial* view_mat = new LambertianMaterial(blacktex, viewtex);

    Instance* window_ins = new Instance(window);
    BBox w_bounds = window_ins->getBounds();
    
                                
    Triangle* view_l = new Triangle(Point(w_bounds.min.x, -24.5, w_bounds.min.z),
                                    Point(w_bounds.min.x, -24.5, w_bounds.max.z), 
                                    Point(w_bounds.max.x, -24.5, w_bounds.min.z), bottomleft, view_mat);

    Triangle* view_r = new Triangle(Point(w_bounds.max.x, -24.5, w_bounds.max.z),
                                    Point(w_bounds.max.x, -24.5, w_bounds.min.z), 
                                    Point(w_bounds.min.x, -24.5, w_bounds.max.z), topright, view_mat);
    
    
    scene->add(view_l);
    scene->add(view_r);
    
    // sphere 
    scene->add(new Sphere(Point(0, -20.5, 2.6168), 0.25f, nullptr, dielectric_mat));


    //Lights
    //daylight
    ConstantTexture *daylighttex = new ConstantTexture(RGBColor(100.0f, 100.0f, 84.0f));
    Material *daylightsource = new LambertianMaterial(daylighttex, blacktex);
    Quad* daylight_quad = new Quad(Point(w_bounds.min.x+0.35, -20, w_bounds.min.z-0.25), 
                                Vector(w_bounds.max.x - w_bounds.min.x , 0,0),
                                Vector(0,0, w_bounds.min.z - w_bounds.max.z),
                                nullptr, daylightsource);
    
    AreaLight daylight(daylight_quad);

    
    //camtotable
    Point fw_min = Point(-0.8, -22.f, -2.209);
    Point fw_max = Point(1.43f, -22.f, -0.5829);
    Quad* camtotablelight = new Quad(Point(source.x+fw_min.x, source.y-0.5, source.z), Vector(fw_max.x, 0.5, 0), Vector(fw_max.x, 0, fw_max.z - fw_min.z), nullptr, 
                                    new LambertianMaterial(new ConstantTexture(RGBColor::rep(300.f)), blacktex));
    AreaLight camtotablesource(camtotablelight);
    

    scene->rebuildIndex();
    
    World* world = new World();
    world->scene = scene;
    world->light.push_back(&camtotablesource);
    world->light.push_back(&daylight);
    
    return world;
    Point source(-0.5f,-3.f, -0.5f);

    float vertical_angle = pi/8.f;
    float cam_ratio = 800.f/528.f;
    float aspect_ratio = 800.f/600.f;
    float horizontal_angle = cam_ratio * vertical_angle;
    
    RecursiveRayTracingIntegrator integrator(world);


    PerspectiveCamera cam(source, Vector(0,-1,0), Vector(0, 0, -1), vertical_angle, horizontal_angle);
    
    int numSamples = 1;
    
    // Low Quality ///

    int width_l = 480;
    int height_l = 480 / aspect_ratio; 
    Image img_lq(width_l,height_l);

    Renderer engine1(&cam, &integrator);
    
    if(numSamples > 1){
        engine1.setSamples(numSamples);
    }
    engine1.render(img_lq);
    img_lq.writePNG("../rc_results/rc_low.png");

}




void a_competition(){
    //World* world = create_scene();
    create_scene();
    /// High Quality ///

    // Renderer engine2(&cam, &integrator);
    
    // int width_h = 1920;
    // int height_h = 1920 / aspect_ratio; 
    // Image img_hd(width_h,height_h);

    // if(numSamples > 1){
    //     engine2.setSamples(numSamples);
    // }
    // engine2.render(img_hd);
    // img_hd.writePNG("../rc_results/rc_high.png");

    
    
}