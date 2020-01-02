## How to start

```bash
docker run -d --rm --name mkdocs -v $PWD:/doc -p 8000:8000 mkdocs
```

## How to deploy manually

```bash
docker run --rm --name mkdocs \
    -v $PWD:/doc \
    -v $HOME/.ssh/known_hosts:/root/.ssh/known_hosts \
    -v $HOME/.ssh/roomhub-mkdocs-build:/root/.ssh/id_rsa \
    mkdocs gh-deploy -f docs/mkdocs.yml
```

## How to deploy from CI

1. Set up your GitHub personal access token as `GITHUB_PAT` environment variable in build
2. Change Git remote with:

    ```bash
    git remote set-url origin https://$GITHUB_PAT@github.com/aetas/RoomHub.git
    ```

3. Deploy with command:

    ```bash
    docker run --rm --name mkdocs -v $PWD:/doc mkdocs gh-deploy -f docs/mkdocs.yml
    ```
