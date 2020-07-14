list=$(cat .gitmodules | grep url)
while IFS= read -r line; do
    X=" = "
    read -a strarr <<<"$line"
    git submodule add ${strarr[2]}
done <<< "$list"
