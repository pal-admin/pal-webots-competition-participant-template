# webots-competition-competitor

[![Webots Badge](https://badgen.net/badge/icon/Rankings?label=Webots)](https://cyberbotics.github.io/webots-competition-organizer-template/)

## Register

- Make a new repository out of [the template](https://github.com/pal-admin/pal-webots-competition-participant-template/generate).
- \[optional: only if you created a private repository\]: Add `pal-admin` to [Manage access](https://docs.github.com/en/free-pro-team@latest/github/administering-a-repository/managing-teams-and-people-with-access-to-your-repository#inviting-a-team-or-person) section. This allows the organizers to be able to clone your repository via [pal-admin](https://github.com/pal-admin).
- Add your repository to [competitors.txt](https://github.com/pal-admin/pal-webots-competition-organizer/edit/master/competitors.txt).

## Develop

Download and install [Webots](https://github.com/cyberbotics/webots/releases/latest) on your local computer.

Create the following directory structure:

```bash
git clone https://github.com/pal-admin/pal-webots-competition-organizer.git
git clone [url_to_this_repo] pal-webots-competition-organizer/controllers/participant_controller
```

Run the simulation, you can change `competition1.wbt` for any other map:

```bash
webots pal-webots-competition-organizer/worlds/competition1.wbt
```

Once you are satisfied with the result, you can push the changes:
```bash
cd pal-webots-competition-organizer/controllers/participant_controller
git add -A
git commit -m "Great improvement"
git push
```

## Results

You can check the results of the competition at [pal-admin.github.io/pal-webots-competition-organizer](https://pal-admin.github.io/pal-webots-competition-organizer).
